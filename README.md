# push to arduino

réécriture en nodeJs d'un programme existant en PHP en n'ayant plus qu'un seul serveur.

Une fois démarré, le serveur expose une page web qui est un client via websocket du serveur.
Chaque client peut envoyer du code Arduino vers le serveur.
Le serveur gère un système de file Fifo pour que chaque client attende son tour.
Une fois le code téléversé, le code du client tourne pendant 30 secondes avant qu'un autre code le remplace( si il y a une demande dans la file)


# how to

C'est un programme **nodejs** il faut donc installer nodejs
Il faut aussi installer
**arduino-cli**
  
L'executable est founit mais il faut sans doute lancer une commande d'initialisation ... je n'ai pas noté cette commande ... ouppsss



ensuite faire 

>npm install

puis 

>node index.js



# what if 

si le programme s'arrete dès le début c'est peut etre que la carte arduino n'est pas branché
