'use strict';

const express = require('express')
const http = require('http')
const fs =require('fs')
const app = express()
const WS = require('ws')
const server = http.createServer(app);
const port = 8080
const { spawn, spawnSync } = require( 'child_process' );
const { exit } = require('process');


const wss = new WS.WebSocket.Server({ server});
var clients = [];
var nbClient = 0;
var fifoTeleverse = [];
var fifoCompile = [];
var board;
var portboard;

console.log('connecting to board');
const initProcess = spawnSync( 'arduino-cli', [ 'board', 'list','--format' ,'json' ] );

//ls.stdout.on( 'data', ( data ) => console.log( `stdout: ${ data }` ) );
//ls.stderr.on( 'data', ( data ) => console.log( `stderr: ${ data }` ) );
//ls.on( 'close', ( code ) => { console.log( `child process exited with code ${code}` ); exit(code) } );
if ( initProcess.stderr != undefined && initProcess.stderr.toString().length > 0) {
    console.log("RETOUR ERR : "+ initProcess.stderr)
    exit(1);
}

console.log("RETOUR OUT : "+ initProcess.stdout)
var tmpJson = JSON.parse(initProcess.stdout.toString());
if ( tmpJson.length >= 1) {
    var index =0;
    while(board == undefined && index < tmpJson.length) {
        if (tmpJson[index].matching_boards != undefined && tmpJson[index].port != undefined) {
            board = tmpJson[index].matching_boards[0].fqbn;
            portboard = tmpJson[index].port.address;
            console.log('Found a '+board+ ' on port ' + portboard)
        } 
        index++;
    }

    if ( board == undefined) {
      console.log('board not found. i dont understand JSON info . plug the board and restart ');
      exit(2);
    }

} else {
    console.log('board not found. plug the board and restart ');
    exit(2);
}

//$json = $json[2]; ///ATTENTION DOIT ETRE CHANGER ICI

//$board = $json->{'matching_boards'}[0]->{'fqbn'};
//$portboard = $json->{'port'}->{'address'};
//echo "Trouve : ".$board." sur le port ".$portboard."\n";


wss.on('connection', (ws,req) => {

    const ip = req.headers.host;
    //const headers = req.headers.host
    //console.log('URL : ' + JSON.stringify(headers))
   
    var clientId = nbClient++;
    clients.push({id: clientId, ws: ws});
    
    ws.isAlive = true;

    ws.on('pong', () => {
        ws.isAlive = true;
    });

    //Quand on reçoit un message du client
    ws.on('message', (message) => {

        //on parse le message et on l'ajoute sur la fifoCompile. 
        // Avant de l'ajouter sur la fifoCompile on essaye de le compiler . 
        // si ça compile pas, on alerte et on ne met finalement pas dans la fifoCompile
        console.log('received: %s', message);
        var msg = JSON.parse(message)
        var userId = msg.id;
        var userMsg = msg.message;
        fifoCompile.push(msg);
        var num = fifoCompile.length;
        //var response = { type: 'msg', id:userId, message: 'votre commande a été ajouté dans file de compilation, vous êtes N° '+ num}; 
        //ws.send(JSON.stringify(response));
        sendMessageInitCompile(userId, 'votre commande a été ajouté dans file de COMPILATION, vous êtes N° '+ num,num)
        AjoutDansCompileFifoFait(userId);
    });
    
    //send immediatly a feedback to the incoming connection   
    ws.send(JSON.stringify({type: 'system',id: clientId, })); 
    ws.send(JSON.stringify({type: 'system',message: `Bonjour ${ip}, `}));
    ws.send(JSON.stringify({type: 'system',message: `Je suis le serveur du mur de leds`}));
    ws.send(JSON.stringify({type: 'system',message: `Tu es le client N° ${clientId}`}));
});


//ATTENTION cette partie a été mise en commentaire car ça ne fonctionne pas sur le PC de l'ENSIM.(pb d'encodage qui fait planter le ping.)
// pour vérifier qu'on a bien des sockets vivantes mais pas certain que ça fonctionne activement ... 
// setInterval(() => {
//     wss.clients.forEach((ws) => {
//         //console.log('ping client !')
//         if (!ws.isAlive) return ws.terminate();
        
//         ws.isAlive = false;
//         ws.ping(null, false, true);
//     });
// }, 10000);


// ici c'est le code qui regarde toutes les secondes si il peut téléverser QQ chose .
var televersementEnCours =false;
setInterval(() => {
    //console.log('televersement ? ')
    //si pas de televersement en cours, on dépile le prochain et on televerse
    //sinon on ne fait rien
    if ( televersementEnCours == true) {
        //on ne fait rien
        //console.log('televersementEnCours donc on ne fait rien ')
    } else {
        televersementEnCours = true
        //console.log('fifoTeleverse.length ? ' + fifoTeleverse.length)
        if ( fifoTeleverse.length > 0) {
            var data = fifoTeleverse.shift()
            var currentClient = findClient(data.id);
            if ( currentClient.ws != undefined ) {
                sendStartTeleverse(data.id);
                //on televerse
                fs.writeFile('./codeTemp/codeTemp.ino', data.message, function (err) {
                    if (err) {
                        console.log('Oupppppsss pb : ' +err);    
                    } else {
                        //console.log('It\'s saved!');
                      //  console.log('arduino-cli compile -p '.$portboard.' --fqbn '.$board.' txt --format json --upload');
                        const televerseProcess = spawn( 'arduino-cli', [ 'compile', '-p',portboard , '--fqbn' ,board ,'codeTemp', '--format', 'json', '--upload' ] );
                        
                        var err = '';
                        var out = '';
                        televerseProcess.stdout.on( 'data', ( data ) => {
                           // console.log( `stdout: ${ data }` ) 
                            out += data;
                        });
                        televerseProcess.stderr.on( 'data', ( data ) => {
                           // console.log( `stderr: ${ data }` ) 
                            err += data;
                        });
                        televerseProcess.on( 'close', ( code ) => {
                            console.log( `child process exited with code ${code}` ) 
                            var processOut = JSON.parse(out);
                            if ( err.length > 0) {
                                sendErrorTeleverse(data.id,processOut.compiler_err)
                                televersementEnCours = false
                            } else {
                                sendSuccessTeleverse(data.id)
                                broadcast("Execution du programme du client "+ data.id + " pendant 30 secondes minimum");
                                setTimeout(() => {
                                    broadcast("Fin de l'éxecution du programme du client "+ data.id );
                                    televersementEnCours = false
                                }, 60000);
                            }
                            
                           
                        } );
                    }
                     //a la fin on 
                     //televersementEnCours = false
                  });
            } else {
                // la websocket n'est plus vivante ==> on degage de la file.
                console.log("le client n'est plus présent, on passe a la demande suivante")
                televersementEnCours = false
            }

        } else {
            //console.log('non y a rien ')
        //a la fin on 
        televersementEnCours = false
        }

       
    }
}, 10000);


// ici c'est le code qui regarde toutes les secondes si il peut compiler QQ chose .
var compilationEnCours =false;
setInterval(() => {
    //console.log('compile ? ')
    //si pas de compilation en cours, on dépile le prochain et on compile
    //sinon on ne fait rien
    if ( compilationEnCours == true) {
        //on ne fait rien
        console.log('compilationEnCours donc on ne fait rien ')
    } else {
        compilationEnCours = true
        //console.log('fifoCompile.length ? ' + fifoCompile.length)
        if ( fifoCompile.length > 0) {
            var data = fifoCompile.shift()
            shiftDansCompileFifoFait();
            var currentClient = findClient(data.id);
            if ( currentClient.ws != undefined ) {
                sendStartCompile(data.id);
                //on compile
                fs.writeFile('./compileTemp/compileTemp.ino', data.message, function (err) {
                    if (err) {
                        console.log('Oupppppsss pb : ' +err);    
                    } else {
                        console.log('It\'s saved!');
                      //  console.log('arduino-cli compile -p '.$portboard.' --fqbn '.$board.' txt --format json');
                        const televerseProcess = spawn( 'arduino-cli', [ 'compile', '-p',portboard , '--fqbn' ,board ,'compileTemp', '--format', 'json' ] );
                        
                        var err = '';
                        var out = '';
                        televerseProcess.stdout.on( 'data', ( data ) => {
                           // console.log( `stdout: ${ data }` ) 
                            out += data;
                        });
                        televerseProcess.stderr.on( 'data', ( data ) => {
                           // console.log( `stderr: ${ data }` ) 
                            err += data;
                        });
                        televerseProcess.on( 'close', ( code ) => {
                            console.log( `child process exited with code ${code}` ) 
                            var processOut = JSON.parse(out);
                            if ( err.length > 0) {
                                sendErrorCompile(data.id,processOut.compiler_err)
                            } else {
                                sendSuccessCompile(data.id)
                                fifoTeleverse.push(data);
                                var num = fifoTeleverse.length;
                                //var response = { type: 'msg', id:userId, message: 'votre commande a été ajouté dans file de téléversement, vous êtes N° '+ num}; 
                                //ws.send(JSON.stringify(response));
                                sendMessageInitTeleverse(data.id, 'votre commande a été ajouté dans file de TELEVERSEMENT, vous êtes N° '+ num,num)
                                AjoutDansFifoFait(data.id)
                            }
                            shiftDansFifoFait()
                            compilationEnCours = false
                        } );
                    }
                     //a la fin on 
                     //compilationEnCours = false
                  });
            } else {
                // la websocket n'est plus vivante ==> on degage de la file.
                console.log("le client n'est plus présent, on passe a la demande suivante")
                shiftDansFifoFait()
                compilationEnCours = false
            }

        } else {
            //console.log('non y a rien ')
        //a la fin on 
        compilationEnCours = false
        }

       
    }
}, 10000);

// pour exposer la page web
app.use(express.static('front'))

// ne sert a rien.
app.get('/alive', (req, res) => {
  res.send('alive')
})

//démarrage du serveur HTTP
server.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})





function systemMsg(ws, id, msg ){
    ws.send(JSON.stringify({type: 'system',message: msg, id: id}));
}
function sendMessage(id, msg,pos ){
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        client.ws.send(JSON.stringify({type: 'msg',message: msg, id: id, pos: pos}));
    }
    
}

function sendMessageInitCompile(id, msg,pos ){
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        client.ws.send(JSON.stringify({type: 'msg',message: msg, id: id, pos: pos,init: 'compile'}));
    }
    
}

function sendMessageInitTeleverse(id, msg,pos ){
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        client.ws.send(JSON.stringify({type: 'msg',message: msg, id: id, pos: pos,init: 'televerse'}));
    }
    
}


function sendStartTeleverse(id) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"C'est votre tour, Votre programme va être téléversé ");
    }
}

function sendSuccessTeleverse(id) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"Bravo votre programme a été téléversé ");
    }
}

function sendErrorTeleverse(id,errMsg) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"Il y a eu un soucis au téléversement ");
        systemMsg(client.ws,id,errMsg);
    }
}

function sendStartCompile(id) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"C'est votre tour, Votre programme va être compilé ");
    }
}

function sendSuccessCompile(id) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"Bravo votre programme a été compilé ");
    }
}

function sendErrorCompile(id,errMsg) {
    var client = findClient(id);
    if ( client != undefined && client.ws != undefined) {
        systemMsg(client.ws,id,"Oups ! Il y a eu un soucis à la compilation ");
        systemMsg(client.ws,id,errMsg);
    }
}

function findClient(id) {
    return clients.find(e => e.id == id);
}


function broadcast(msg) {
    wss.clients
    .forEach(client => {
        
            client.send(JSON.stringify({type: 'systemBroadcast', message: msg}));
            
    });
}

function broadcastAllBut(id,msg) {
    var notToBroadCastClient =findClient(id);
    wss.clients
    .forEach(client => {
            if ( client != notToBroadCastClient.ws) {
                client.send(JSON.stringify({type: 'systemBroadcast', message: msg}));
            }
    });
}

function AjoutDansFifoFait(id){
    //Broadcast
    broadcastAllBut(id,"Add");
}
	
function shiftDansFifoFait(){
	//Broadcast
	broadcast("Next");
}

function AjoutDansCompileFifoFait(id){
    //Broadcast
    broadcastAllBut(id,"AddComp");
}
	
function shiftDansCompileFifoFait(){
	//Broadcast
	broadcast("NextComp");
}