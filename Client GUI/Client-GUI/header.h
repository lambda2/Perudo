/**
 * \file header.h
 * \brief Cette entête est commune au client et au serveur.
 * \author Aubin.A
 * \version 1.0
 * \date 29 avril 2011, 16:12
 *
 * Ce fichier définit :
 * - le contenu de la structure Paquet
 * - l'énumération phasePartie
 * - les constantes pour le port par defaut, le nombre de tentatives de connexion
 * avant abandon de la connexion et si le mode de débogage est activé ou non.
 *
 * Elle contient aussi toutes les inclusions nécessaires au bon fonctionnement
 * du serveur et du client (sockets, threads etc...)
 * 
 */


# pragma once

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>        // support des threads
#include <sstream>          // stringstream
#include <iostream>
#include <string>
#include <fstream>


    using namespace std;


#include <time.h>       // Necessaire pour un calage aléatoire du rand()

#define DEF_PORT 1363   // Port par defaut
#define DEBUG 0         // debug activé ou non
#define NB_TENTATIVES 5 // Nombre de tentatives avant abandon de la connexion

/**
 * \enum phasePartie
 * \brief drapeau d'état du paquet
 * Cette énumération définit les différents états que peut avoir la variable
 * flag dans un paquet. Elle sert a synchroniser le client et le serveur en
 * les mettant d'accord sur le déroulement de la partie
 */
typedef
enum {
    ATTENTE_ADMIN   = 0,            // En attente de l'admin
    ATTENTE_JOUEURS = 1,            // En attente des joueurs
    FIN_MANCHE      = 2,            // La manche est finie
    FIN_PARTIE      = 3,            // La partie est finie
    INDEFINI        = 4,            // FLAG par defaut
    OK              = 5,            // Ok. (généralement pour accuser reception)  (Client <-> Serveur)
    D_PARI          = 6,            // Demande de pari                            (Serveur -> Client)
    RESULT          = 7,            // Resultats de la manche                     (Serveur -> Client)
    R_PARI          = 8,            // Retour de pari                             (Client  -> Serveur)
    ERR_PARI        = 9,            // Erreur sur le pari du client               (Serveur -> Client)
    LANCER          = 10,           // Communiqué du lancer de des                (Serveur -> Client)
    _MSG            = 11,           // Message a afficher                         (Serveur -> Client)
    START           = 12,           // Debut de partie                            (Serveur -> Client)
    VIERGE          = 13,           // paquet vierge                              (Serveur -> Client)
    N_MANCHE        = 14            // Nouvelle manche de jeu                     (Serveur -> Client)
}
phasePartie;

/**
 * \struct Paquet header.h
 * \brief Informations échangées entre le client et le serveur
 * Cette structure contient toutes les données qui transitent entre
 * le client et le serveur.
 */
struct Paquet {
    char pseudo[20];        // le pseudo du joueur
    int lancer[5];          // son lancer de dés
    int pari_nb_de;         // son pari sur le nombre de dés
    int pari_face_de;       // son pari sur la valeur du dé
    int id;                 // l'identifiant (unique) du joueur
    int nbDes;              // le nombre de dés qu'a le joueur
    char nomPartie[20];     // le nom de la partie
    int nbJoueurs;          // le nombre de joueurs de la partie
    char msg[500];          // un texte à afficher
    bool inGame;            // vrai si le joueur joue toujours
    phasePartie flag;       // état de la partie
    int precPariNbDes;      // pari du nombre de dés du joueur précédent
    int precPariValDes;     // pari de la valeur du dé du joueur précédent
};

