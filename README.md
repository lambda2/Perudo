Perudo
======

Le répertoire du projet contient deux répertoires :
----------------------------------------------------

– Serv : contient les sources du serveur
– Client-GUI : contient les sources et les ressources du client.

Le serveur marche **exclusivement sur console**, et est normalement portable sous windows
en ajoutant les paramètres `-lpthread` (et sous windows : `-lwsock32`).

`g++ -g -o serv main.cpp Linker.cpp LServeur.cpp ../LDebug.cpp Gestionnaire.cpp -lpthread`

Le client marche en graphique et sous console, et démarre en mode graphique par défaut.
On peut le démarrer sous console en lui donnant -c comme argument de ligne de
commande.

La partie graphique n'est pas entièrement achevée, elle contient de gros bugs de
« freeze », c'est a dire que quand on se déconnecte, ou quand on ne joue pas, la fenêtre
ne répond plus. On reprend la main lorsque c'est à notre tour.

Tous les fichiers sources dont documentés en Doxygen, le fichier de configuration est
(normalement) dans le répertoire.
Pour compiler le client, il est nécessaire de passer par Qt, autrement dit :
```
Qmake -project
Qmake
make
```
Lorsque que l'on joue en mode console, pour déclarer un dudo (c'est a dire qu'on
pense que le joueur précédent a tout faux), on parie sur 0 dés de valeur 0.
