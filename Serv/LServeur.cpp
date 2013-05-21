/* 
 * File:   LServeur.cpp
 * Author: lambda2
 * 
 * Created on 5 avril 2011, 23:20
 */

 /**
 * \file LServeur.cpp
 * \brief
 * \author lambda2
 * \version 1.0
 * \date 5 avril 2011, 23:20
 */
#include "LServeur.h"

/**
 * \brief Constructeur
 * 
 * Constructeur de la classe LServeur
 * 
 */
LServeur::LServeur() {
    this->initialiserServeur();
    this->dbg << " * le serveur a démarré.";o();
   // recsize = sizeof(csin);
    compteurClient=0;
    NB_JR_MAX=0;
    joueurPresent=false;
    joueursConnectes=0;
    idCourante=0;
    /* Si les sockets Windows fonctionnent */
    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }
    
}

/**
 * \brief constructeur de copie
 * @param orig LServeur a copier
 */
LServeur::LServeur(const LServeur& orig) {
}

/**
 * \brief Destructeur
 */
LServeur::~LServeur() {
    if(tabClient!=NULL)
    {
        delete [] tabClient;
    }
    if(Jeu!=NULL)
        delete Jeu;
}

/**
 * \brief Initialise le serveur
 */
void LServeur::initialiserServeur() {
     #if defined (WIN32)
        WSADATA WSAData;
        erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        erreur = 0;
    #endif
        tabClient=NULL;
        tabClient=NULL;
        Jeu=NULL;
        port=DEF_PORT;
}

/**
 * \brief connecte le serveur au reseau sur le port donné par le client
 * @return true si il est amorcé correctement
 * \see LServeur::setPort(int _port)
 */
bool LServeur::amorcer() {
    if(sock != INVALID_SOCKET)
    {
        
        printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

        /* On configure tout ca... :D */
        sin.sin_addr.s_addr    = htonl(INADDR_ANY);   /* Adresse IP automatique */
        sin.sin_family         = AF_INET;             /* Protocole familial (IP) */
        sin.sin_port           = htons(port);         /* Listage du port */
        sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
    }
    /* Si la socket est OK */
    if(sock_err != SOCKET_ERROR)
    {
        /* On ecoute */
        sock_err = listen(sock, 5);
        printf("Listage du port %d...\n", port);
        return true;
        
    }
    else
    {
        cout << "erreur socket." << endl;
        return false;
    }
}

/**
 * \brief mutateur de port
 * @param _port
 */
void LServeur::setPort(int _port) {
    port = port;
}

/**
 * \brief méthode apellée lors de la connexion du premier joueur
 * attend une connexion, puis demande au premier connecté de parametrer
 * le serveur avec la methode configurerPartie(), puis l'enregistre.
 * \see void LServeur::enregistrer(Linker *link, int position)
 */
void LServeur::attendreAdmin() {
    Linker *p_client = (Linker*) malloc (sizeof *p_client);
    if(isFirstLogin())
    {
        if (p_client != NULL)
        {
            if(socketOk())
            {
                p_client->setRecsize();
                /* le client se ramene... */
                printf("l'administrateur se connecte sur le port %d...\n", port);
                this->dbg << " - Administrateur connecté";o();
                p_client->accepterAdmin(sock);
                joueurPresent=true;
                this->dbg << " - Administrateur accepté";o();
                p_client->newThreadEnvoi();
                pthread_join (p_client->getThread(), NULL);
                p_client->newThreadRecept();
                pthread_join (p_client->getThread(), NULL);
                configurerPartie(p_client);
                enregistrer(p_client,compteurClient);
                // <editor-fold defaultstate="collapsed" desc="else">
            } else
                printf("Erreur de transmission\n"); // ERREUR A CATCHER
        } else {
            fprintf(stderr, "erreur memoire lors de la creation administrateur\n");
        }
    } else {
        fprintf(stderr, "erreur lors de la creation administrateur : un admin est deja present\n");
    }// </editor-fold>

}

/**
 * \brief méthode apellée lors de la connexion d'un joueur
 * Attend un joueur et l'enregistre.
 */
void LServeur::nouveauClient() {
    if(compteurClient == 0 || NB_JR_MAX == 0)
    {
        this->dbg << "\t ! SERVEUR NON CONFIGURE";o();
    }
    else
    {
        while(compteurClient != NB_JR_MAX)
        {
            if(!isFirstLogin())
            {
                int end=0;
                do
                {
                    Linker *p_client = (Linker*) malloc (sizeof *p_client);
                    p_client->initialiserPaquet();
                    if (p_client != NULL)
                    {

                        if(socketOk())
                        {
                            p_client->setRecsize();
                        /* le client se ramene... */
                            printf("le client se connecte sur le port %d...\n", port);
                            this->dbg << " - Un client s'est connecté.";o();
                            p_client->accepter(sock);
                            this->dbg << " - Nouveau client accepté.";o();
                            enregistrer(p_client,compteurClient);
                            printf("Le client s'identifie, veuillez patienter...");

                            p_client->newThreadEnvoi();
                            pthread_join (p_client->getThread(), NULL);
                            p_client->newThreadRecept();
                            pthread_join (p_client->getThread(), NULL);

                            end=1;
                        }
                // <editor-fold defaultstate="collapsed" desc="else">
            else
                            printf("Erreur de transmission\n");
                    }
                    else
                    {
                        fprintf (stderr, "erreur memoire lors de la creation client\n");
                    }
                }// </editor-fold>
                while (!end);
            }
        }
    }
}

/**
 * \brief enregistre le joueur [*link] à la position [position]
 * @param link pointeur sur le joueur a enregistrer
 * @param position position a laquelle enregistrer le joueur
 */
void LServeur::enregistrer(Linker *link, int position) {
    if (position >= 0 && position < NB_JR_MAX) {
        tabClient[position] = link;
        tabClient[position]->setNbDes(5);
        tabClient[position]->setId(position);
        compteurClient++;

        this->dbg << " - Le client "
                << tabClient[position]->getLogin() << " est enregistré avec l'ID "
                << position;
        o();
    }
}

/**
 * \brief recoit un paquet du joueur dont l'id est donnée en parametre.
 * @param id id du joueur qui va nous envoyer quelque chose
 */
void LServeur::recevoirPaquet(int id) {
    tabClient[id]->newThreadRecept();
    this->dbg << "\t (T) Nouveau thread crée [recv]";
    o();
}

/**
 * \brief envoie un paquet au joueur dont l'id est donnée en parametre.
 * @param id id du joueur a qui on va envoyer quelque chose
 * @param msg message a envoyer (optionnel)
 */
void LServeur::envoyerPaquet(int id, const char* msg) {
    tabClient[id]->newThreadEnvoi();
    this->dbg << "\t (T) Nouveau thread crée [send]";
    o();
    pthread_join(tabClient[id]->getThread(), NULL);
    this->dbg << "\t (T) Fin du thread [send]";
    o();
}

/**
 * \brief ferme la socket du serveur.
 */
void LServeur::fermer() {
    /* Fermeture de la socket */
    this->dbg << " + Fermeture de la socket...";
    o();
    closesocket(sock);
    this->dbg << " + le serveur est fermé.";
    o();


#if defined (WIN32)
    WSACleanup();
#endif
}

/**
 * \brief configure la partie avec la configuration donnée
 * par link->getConfig(nomDeLaPartie);
 * @param link joueur qui contient les information de configuration
 */
void LServeur::configurerPartie(Linker *link) {
    NB_JR_MAX = link->getConfig(nomDeLaPartie);
    this->dbg << " - La partie [" << nomDeLaPartie << "] est configurée pour " << NB_JR_MAX << " joueurs.";
    o();
    printf("Serveur %s configuré pour %d joueurs\n", nomDeLaPartie, NB_JR_MAX);
    tabClient = new Linker*[NB_JR_MAX];
    memset(tabClient, 0, sizeof (tabClient));
    this->dbg << " - $tabClient = NEW Linker[" << NB_JR_MAX << "]";
    o();
}

/**
 * @return true si le joueur est le premier connecté
 */
bool LServeur::isFirstLogin() {
    if (!joueurPresent)
        return true;
    else
        return false;
}

/**
 * @return true si le socket n'a pas d'erreur
 */
bool LServeur::socketOk() {
    if (sock_err != SOCKET_ERROR)
        return true;
    else
        return false;
}

/**
 * \brief envoie le message en parametre a tous les joueurs
 * @param msg message a envoyer
 */
void LServeur::broadcast(char* msg) {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->setmsg("Bienvenue sur le serveur.\nVous êtes actuellement en attente des autres joueurs.");
        envoyerPaquet(i);
    }
}

/**
 * \brief méthode qui ne s'arrete que quand tous les joueurs ont rejoint la partie
 */
void LServeur::attenteJoueurs() {
    if (NB_JR_MAX == 0) {
        printf("Attente des joueurs impossible : serveur non configuré");
    } else {
        printf("En attente des autres joueurs (%d)", NB_JR_MAX);
        while (joueursConnectes != NB_JR_MAX) {
        }
    }
}

/**
 * \brief fontion de debug qui affiche l'état général du serveur
 */
void LServeur::etatServeur() {
    cout << "compteurClient = " << compteurClient << endl;
    cout << "NB_JR_MAX = " << NB_JR_MAX << endl;
    cout << "joueurPresent = " << joueurPresent << endl;
    cout << "joueursConnectes = " << joueursConnectes << endl;
    cout << "nomDeLaPartie = " << nomDeLaPartie << endl;
    afficherTab();
    cout << endl;

}

/**
 * \deprecated n'est plus utilisée.
 */
void LServeur::etatTab(Linker* linker, int limite) {
    for (int i = 0; i <= limite; i++) {
        cout << "ETAT PAQUET N°" << i << endl <<
                "nbDes : " << linker[i].getNbDes() << endl;
    }
}

/**
 * \deprecated n'est plus utilisée.
 */
void LServeur::afficherTab(int index) {
    for (int i = 0; i < compteurClient; i++)
        cout << "tabClient[" << i << "].getNbDes()=" << tabClient[i]->getNbDes();
}

/**
 * \brief envoie a tous les jouers le signal de début de la partie.
 */
void LServeur::sig_DebutPartie() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->setmsg("La partie est prête a commencer.");
        tabClient[i]->setFlag(START);
        envoyerPaquet(i);
    }
}

/**
 * \brief allocation de Gestionnaire avec les infos de configuration.
 */
void LServeur::initialiserJeu() {
    if (socketOk() && serveurConfigure())
        Jeu = new Gestionnaire(tabClient, NB_JR_MAX);
}

/**
 * @return true si le serveur est configuré
 */
bool LServeur::serveurConfigure() {
    if (compteurClient == 0 || NB_JR_MAX == 0)
        return false;
    else
        return true;
}

/**
 * \brief lance les dés de tous les joueurs
 */
void LServeur::lancerTousLesDes() {
    for (int i = 0; i < NB_JR_MAX; i++)
        tabClient[i]->lancerDes();
}

/**
 * \brief envoie les lancers de chaque joueur
 */
void LServeur::envoyerDes() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->setFlag(LANCER);
        this->envoyerPaquet(i);
    }
}

/**
 * \brief envoie le signal de nouvelle manche a chaque joueur
 */
void LServeur::nouvelleManche() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->setFlag(N_MANCHE);
        this->envoyerPaquet(i);
    }
}

/**
 * attend tant que tous les joueurs n'ont pas envoyé le flag donné en parametre
 * @param phase flag a attendre
 */
void LServeur::attendre(phasePartie phase) {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->attendre(phase);
    }
}

/**
 * \brief méthode qui va gerer le jeu.
 * Tant que la partie n'est pas finie, on enchaine les manches.
 */
void LServeur::jouer() {
    bool finPartie = false;
    while (!finPartie) {
        this->nouvelleManche();
        this->attendre(OK);
        this->lancerTousLesDes();
        this->envoyerDes();
        this->attendre(OK);
        finPartie = Jeu->phase_two();
    }
    Jeu->declarerFinPartie();
}

/**
 * @return l'id du joueur précédent au joueur actuel
 */
int LServeur::joueurPrecedent() const {
    int id = 0;
    if (idCourante == 0)
        id = NB_JR_MAX - 1;
    else
        id = idCourante - 1;
    return id;
}

/**
 * @return l'id du joueur suivant au joueur actuel
 */
int LServeur::joueurSuivant() const {
    int id = 0;
    if (idCourante == NB_JR_MAX - 1)
        id = 0;
    else
        id = idCourante + 1;
    return id;
}

/**
 *\deprecated n'est plus utilisée : projet qui n'a pas abouti.
 */
void LServeur::demanderParis(int i) {
    int partie = 0;
    tabClient[i]->pari();
    while (partie != 5) {
        tabClient[i]->attendre(R_PARI);

        //----------------- PARTIE GEREE PAR LE GESTIONNAIRE -----------------//


        //--------------- FIN PARTIE GEREE PAR LE GESTIONNAIRE ---------------//
        switch (partie) {
                /**
                 * Si le pari est invalide
                 */
            case 0:
                tabClient[i]->setFlag(ERR_PARI);
                tabClient[i]->envoyer();
                break;
                /**
                 * Si le pari est valide
                 */
            case 1:
                tabClient[i]->setFlag(OK);
                tabClient[i]->envoyer();
                idCourante++;
                break;
                /**
                 * Si on a perdu
                 */
            case 2:
                tabClient[i]->setFlag(_MSG);
                tabClient[i]->setmsg("Vous avez perdu");
                break;
        }


    }
}
