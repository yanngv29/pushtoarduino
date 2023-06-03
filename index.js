
const express = require('express')
const http = require('http')
const fs =require('fs')
const app = express()
const WS = require('ws')
const server = http.createServer(app);
const port = 8080

const wss = new WS.WebSocket.Server({ server});
var clients = [];
var nbClient = 0;
var fifo = [];
wss.on('connection', (ws,req) => {

    const ip = req.headers.host;
    //const headers = req.headers.host
    //console.log('URL : ' + JSON.stringify(headers))
    clients.push(ws);
    var clientId = nbClient++;

    ws.isAlive = true;

    ws.on('pong', () => {
        ws.isAlive = true;
    });

    //connection is up, let's add a simple simple event
    ws.on('message', (message) => {

        //log the received message and send it back to the client
        console.log('received: %s', message);
        var msg = JSON.parse(message)
        var userId = msg.id;
        var userMsg = msg.message;
        fifo.push(msg);
        var num = fifo.length;
        var response = { type: 'msg', id:userId, message: 'votre commande a été ajouté dans file, vous êtes N° '+ num}; 
        ws.send(JSON.stringify(response));
    });
    
    //send immediatly a feedback to the incoming connection   
    ws.send(JSON.stringify({type: 'system',id: clientId, })); 
    ws.send(JSON.stringify({type: 'system',message: `Bonjour ${ip}, `}));
    ws.send(JSON.stringify({type: 'system',message: `je suis le serveur du mur de leds`}));
    ws.send(JSON.stringify({type: 'system',message: `tu est le client N° ${clientId}`}));
});

setInterval(() => {
    wss.clients.forEach((ws) => {
        console.log('ping client !')
        if (!ws.isAlive) return ws.terminate();
        
        ws.isAlive = false;
        ws.ping(null, false, true);
    });
}, 10000);

var televersementEnCours =false;
setInterval(() => {
    console.log('televersement ? ')
    //si pas de televersement en cours, on dépile le prochain et on televerse
    //sinon on ne fait rien
    if ( televersementEnCours == true) {
        //on ne fait rien
        console.log('televersementEnCours donc on ne fait rien ')
    } else {
        televersementEnCours = true
        console.log('fifo.length ? ' + fifo.length)
        if ( fifo.length > 0) {
            var data = fifo.shift()
            //on televerse
            fs.writeFile('./codeTemp/codeTemp.ino', data.message, function (err) {
                if (err) {
                    console.log('Oupppppsss pb : ' +err);    
                } else {
                    console.log('It\'s saved!');
                }
                 //a la fin on 
                 televersementEnCours = false
              });
        } else {
            console.log('non y a rien ')
        //a la fin on 
        televersementEnCours = false
        }

       
    }
}, 1000);

app.use(express.static('front'))

app.get('/alive', (req, res) => {
  res.send('alive')
})

server.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})



function broadcast(msg) {
    wss.clients
    .forEach(client => {
        
            client.send(msg);
            
    });
}