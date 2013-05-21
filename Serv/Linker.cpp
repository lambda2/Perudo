/* 
 * File:   Linker.cpp
 * Author: lambda2
 * 
 * Created on 16 mai 2011, 16:38
 */

 /**
 * \file Linker.cpp
 * \brief
 * \author lambda2
 * \version 1.0
 * \date 16 mai 2011, 16:38
 */
 
#include "Linker.h"

/**
 * \brief Constructeur
 * 
 * Constructeur de la classe Linker
 * 
 */
Linker::Linker() {
    initialiserPaquet();
}

/**
 * \brief Constructeur de copie
 * 
 * Constructeur de copie de la classe Linker
 * \param orig
 * 
 */
Linker::Linker(const Linker& orig) {
}

/**
 * \brief Destructeur
 * 
 * Destructeur de la classe Linker
 * 
 */
Linker::~Linker() {
}

/**
 * \brief Donne la taille de csin
 * 
 */
void Linker::setRecsize() {
    recsize = (int) sizeof csin;
}

/**
 * \brief Accepter la connection d'un linker
 * 
 * Accepte la connection d'un joueur à rejoindre la partie
 * \param socket
 * 
 */
void Linker::accepter(SOCKET socket) {
    csock = accept(socket, (SOCKADDR*) & csin, (socklen_t*) & recsize);
    printf("Un Linker se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
    isAdmin = false;
    paquetJoueur.flag = ATTENTE_JOUEURS;
}

/**
 * \brief Accepter la connection de l'admin
 * 
 * Le serveur accepte la connection du 1er joueur et lui donne le role d'admin
 * \param socket
 * 
 */
void Linker::accepterAdmin(SOCKET socket) {
    csock = accept(socket, (SOCKADDR*) & csin, (socklen_t*) & recsize);
    printf("Un Admin se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
    isAdmin = true;
    paquetJoueur.flag = ATTENTE_ADMIN;
}

/**
 * \brief Création et envois d'un nouveau thread
 * 
 * \param msg
 * 
 */
void Linker::newThreadEnvoi(const char* msg) {
    strcpy(paquetJoueur.msg, msg);
    pthread_create(&thread, NULL, th_envoyer, this);
}

/**
 * \brief Réception du nouveau thread créé
 */
void Linker::newThreadRecept() {
    pthread_create(&thread, NULL, th_recevoir, this);
}

/**
 * \brief Accesseur de csock
 * 
 * \return csock
 */
SOCKET Linker::getSocket() {
    return csock;
}

/**
 * \brief Erreur lors de la réception de socket
 * 
 * \return sock_err
 */
int Linker::recevoir() {
    Paquet temp;
    int sock_err = recv(csock, (char*) &temp, sizeof (Paquet), 0);
    recupererPaquet(temp);
    return sock_err;
}

/**
 * \brief Erreur lors de l'envois de socket
 * 
 * \param msg
 * \return sock_err
 * 
 */
int Linker::envoyer(const char* msg) {
    strcpy(paquetJoueur.msg, msg);
    int sock_err = send(csock, (char*) &paquetJoueur, sizeof (Paquet), 0);
    return sock_err;
}

/**
 * \brief Récupération de paquetJoueur
 * 
 * \param temp
 * 
 */
void Linker::recupererPaquet(Paquet temp) {
    paquetJoueur = temp;
}

/**
 * \brief Initialise le paquet avant de le mettre dans paquetJoueur
 *
 */
void Linker::initialiserPaquet() {
    Paquet vide = {
        "",
        {0, 0, 0, 0, 0},
        0,
        0,
        0,
        5,
        "",
        0,
        "",
        1,
        VIERGE,
        -1,
        -1
    };
    paquetJoueur = vide;
}

/**
 * \brief Fermeture du socket
 * 
 */
void Linker::fermerSocket() {
    shutdown(csock, 2);
    printf("fermeture du socket %d...\n", csock);
    closesocket(csock);
}

/**
 * \brief Accesseur de thread
 * 
 * \return thread
 *  
 */
pthread_t Linker::getThread() {
    return thread;
}

/**
 * \brief Accesseur du login
 * 
 * \return le pseudo du joueur
 * 
 */
string Linker::getLogin() {
    return paquetJoueur.pseudo;
}

/**
 * \brief Mutateur de paquetJoueur.id
 * 
 * \param _id
 * 
 */
void Linker::setId(int _id) {
    paquetJoueur.id = _id;
}

/**
 * \brief Mutateur de paquetJoueur.flag
 * 
 * \param flag
 * 
 */
void Linker::setFlag(phasePartie flag) {
    paquetJoueur.flag = flag;
}

/**
 * \brief Accesseur de paquetJoueur.pari_face_de
 * 
 * \return la face du dé parié par le joueur
 * 
 */
int Linker::getPariFaceDe() {
    return paquetJoueur.pari_face_de;
}

/**
 * \brief Accesseur de paquetJoueur.pari_nb_de
 * 
 * \return le nombre de dés pariés par le joueur
 *  
 */
int Linker::getPariNbDes() {
    return paquetJoueur.pari_nb_de;
}

/**
 * \brief Accesseur de paquetJoueur.nbdes
 * 
 * \return le nombre de dés du joueur
 *  
 */
int Linker::getNbDes() {
    return paquetJoueur.nbDes;
}

/**
 * \brief Accesseur de paquetJoueur.id
 * 
 * \return l'id du joueur
 * 
 */
int Linker::getId() {
    return paquetJoueur.id;
}

/**
 * \brief Accesseur de paquetJoueur.lancer[de]
 * 
 * \param de
 * \return le lancé de dé du joueur
 *  
 */
int Linker::getDe(int de) {
    return paquetJoueur.lancer[de];
}

/**
 * \brief Mutateur de paquetJoueur.nbdes
 * 
 * \param nb
 * 
 */
void Linker::setNbDes(int nb) {
    paquetJoueur.nbDes = nb;
}

/**
 * \brief Configuration de la partie
 * 
 * \param nom
 * \return le nombre de joueur
 *  
 */
int Linker::getConfig(char* nom) {
    strcpy(nom, paquetJoueur.nomPartie);
    return paquetJoueur.nbJoueurs;
}

/**
 * \brief Mutateur de paquetJoueur.msg
 * 
 * \param msg
 * 
 */
void Linker::setmsg(const char* msg) {
    strcpy(paquetJoueur.msg, msg);
}

/**
 * \brief Mutateur du pari du joueur précédent
 * 
 * \param val valeur du dé parié
 * \param nb nombre de dés parié
 * 
 */
void Linker::setPariJoueurPrecedent(int val, int nb) {
    paquetJoueur.precPariNbDes=nb;
    paquetJoueur.precPariValDes=val;
}

/**
 * \brief Lance les dés
 * 
 * Lance les dés au joueur
 * 
 */
void Linker::lancerDes() {
    memset(paquetJoueur.lancer, 0, sizeof (paquetJoueur.lancer));
    for (int i = 0; i < paquetJoueur.nbDes; i++) {
        paquetJoueur.lancer[i] = rand() % (6) + 1;
    }
}

/**
 * \brief  Attendre réponse joueur
 * 
 * Attend la réponse d'un joueur afin de poursuivre les phases de la manche
 * \param phase
 * 
 */
void Linker::attendre(phasePartie phase) {
    cout << "en attente de " << phase << " @" << paquetJoueur.pseudo << endl;
    while (paquetJoueur.flag != phase) {
        this->recevoir();
    }
    cout << paquetJoueur.pseudo << " a répondu." << endl;
}

/**
 * \brief Envois un paquet avec le flag à pari
 * 
 */
void Linker::pari() {
    this->setFlag(D_PARI);
    this->envoyer();
}

/**
 * \brief Enlever le dé en fin de manche
 * 
 * Enleve un dé au joueur ayant perdu la manche
 * \return true ou false
 *  
 */
bool Linker::enleverDes() {
    if (paquetJoueur.nbDes == 1) {
        paquetJoueur.nbDes--;
        this->eliminer();
        return true;
    } else if (paquetJoueur.nbDes > 1 && paquetJoueur.nbDes <= 5) {
        paquetJoueur.nbDes--;
        return false;
    } else
        cout << "impossible de supprimer le dé (" << paquetJoueur.nbDes << ")" << endl;
        return true;
}

/**
 * \brief Accesseur de paquetJoueur.lancer
 * 
 * \return lancer du joueur
 *  
 */
int* Linker::getLancer() {
    return paquetJoueur.lancer;
}

/**
 * \brief Envois un paquet avec le flag à ok
 *
 */
void Linker::envoyerPariBon() {
    this->setFlag(OK);
    this->envoyer();
}

/**
 * \brief Envois un paquet avec le flag à ERR_PARI
 *
 */
void Linker::envoyerPariPasBon() {
    this->setFlag(ERR_PARI);
    this->envoyer();
}

/**
 * \brief Indique que le joueur n'est plus dans la partie
 *
 */
void Linker::eliminer() {
    paquetJoueur.inGame = false;
}

/**
 * \brief Indique que le joueur est toujours dans la partie
 *
 */
void Linker::reintegrer() {
    paquetJoueur.inGame = true;
}

/**
 * \brief Indique l'état du joueur
 * 
 * \return true ou false
 *  
 */
bool Linker::isAlive() {
    return paquetJoueur.inGame;
}

/**
 * \brief Accesseur du Mutex
 * 
 * \return l'adresse du mutex
 * \deprecated
 *  
 */
pthread_mutex_t *Linker::getMutex() {
    return &mutex;
}

// ----------------------------- FONCTIONS THREADS -------------------------- //

/**
 * \brief fonction threadée qui appelle la méthode envoyer du client passer en paramètre
 * 
 * \param p_data structure client
 * \return NULL
 *  
 */
void *th_envoyer(void *p_data) // on passe une struct cli en parametre
{

    Linker *p_cli = (Linker*) p_data; // on la cast en cli
    if (p_cli != NULL) {
        int end = 0;
        pthread_mutex_lock(p_cli->getMutex());
        do {
            int sock_err = p_cli->envoyer();

            if (sock_err != SOCKET_ERROR) {
                end = 1;
            }
        } while (!end);
        pthread_mutex_unlock(p_cli->getMutex());
    }

    return NULL;
}

/**
 * \brief fonction threadée qui appelle la fonction recevoir du client passée en paramètre
 *
 * \param p_data struture client
 * \return NULL
 */
void *th_recevoir(void *p_data) // on passe une struct cli en parametre
{
    Linker *p_cli = (Linker*) p_data; // on la cast en cli
    if (p_cli != NULL) {
        int end = 0;
        pthread_mutex_lock(p_cli->getMutex());
        do {

            int sock_err = p_cli->recevoir();

            if (sock_err != SOCKET_ERROR) {
                end = 1;
            }
        } while (!end);
        pthread_mutex_unlock(p_cli->getMutex());
    }

    return NULL;
}




// --------------------------- SURCHARGES OPERATEURS ------------------------ //

/**
 * \brief surcharge de l'operateur =
 */
Linker& Linker::operator =(const Linker& Other) {
    paquetJoueur = Other.paquetJoueur;
    return *this;
}

