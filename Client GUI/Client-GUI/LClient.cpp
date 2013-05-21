/* 
 * File:   LClient.cpp
 * Author: lambda2
 * 
 * Created on 19 avril 2011, 13:42
 */

/**
 *
 * \file LClient.cpp
 * \brief Classe principale du programme client.
 * La classe LClient permet au client de communiquer avec le
 * serveur et d'interpreter les données recues.
 * \author Aubin.A
 * \version 1.0
 * \date 19 avril 2011, 13:42
 *
 */


#include "LClient.h"

/**
 *  \brief Constructeur
 *  Constructeur de la classe LClient
 *
 */
LClient::LClient() {

#if defined (WIN32)
    WSADATA WSAData;
    erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
    erreur = 0;
#endif
    fin_partie = false;
    adresse.clear();
    port=DEF_PORT;
    nomPartie="";
    nbJoueurs=0;
    retour=0;
}

/**
 *  \brief Constructeur de copie
 *
 *  Constructeur de copie de la classe LClient
 *
 */
LClient::LClient(const LClient& orig) {
}

/**
 *  \brief Destructeur
 *
 *  Destructeur de la classe LClient
 *
 */
LClient::~LClient() {
}

/**
 * \brief Paramètre l'adresse ip et le port de connexion
 *
 * Recupère les paramètres de ligne de commande argc et argv du main()
 * et regarde si une adresse et un port particulier ont étés définis.
 * Dans le cas contraire, les valeurs par defaut sont appliquées. (ip : 127.0.0.1)
 * (la valeur par défaut du port est définie dans le header (header.h) )
 * 
 * @param argc nombre d'arguments de la ligne de commande
 * @param argv tableaux contenant les arguments si il y a. (de 1 à argc-1)
 */
void LClient::configurerConnexion(int argc, char** argv) {
    if(argc == 1) {
        this->dbg << " - Aucune adresse définie " << endl << " - valeur par defaut : 127.0.0.1";
        o();
        adresse="127.0.0.1";
        port = DEF_PORT;
    } else if(argc == 2) {
        this->dbg << " - Adresse définie : " << argv[1];
        o();
        adresse=argv[1];
        port = DEF_PORT;
    } else {
        this->dbg << " - Adresse et port définis : " << argv[1] << ":" << argv[2];
        o();
        adresse=argv[1];
        port=atoi(argv[2]);
    }
}

/**
 *  \brief Initialisation
 *
 *  Initialise les attributs de la classe CLient
 *
 */
void LClient::initialiser() {
    if (!erreur) {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        cout << adresse << endl;
        sin.sin_addr.s_addr = inet_addr(adresse.c_str());
        //sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(port);
    }
}

/**
 *  \brief Connexion
 *
 *  Essaye de se connecter via la methode LClient::tryConnexion()
 * \return true si la connexion a réussie, false dans le cas contraire.
 * \see LClient::tryConnexion()
 */
bool LClient::connecter() {
    return this->tryConnexion();
}

/**
 * \brief Tenter une connexion sans tentatives
 *
 *  Essaye de se connecter au serveur. En cas d'échec, elle s'arrete.
 *  \return true si la connexion a réussie, false dans le cas contraire.
 */
bool LClient::connecterClic() {
    bool drap = false;
    if (connect(sock, (SOCKADDR*) & sin, sizeof (sin)) != SOCKET_ERROR) {
        printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
        drap = true;
    }// En cas d'échec, on réessaye !
    else {
        printf("Impossible de se connecter\n");
        drap = false;
    }
    return drap;
}

/**
 *  \brief Tenter une connexion
 *
 *  Essaye de se connecter au serveur. En cas d'échec, elle attents 2 sec et recommence.
 *  Si au bout de 5 (par defaut) tentatives, aucune connexion n'a pue être établie, la méthode s'arrête.
 *  \return true si la connexion a réussie, false dans le cas contraire.
 */
bool LClient::tryConnexion() {
    bool drap = false;
    int count = NB_TENTATIVES;
    // Tant que on n'a pas fait [NB_TENTATIVES] tentatives ET que l'on n'est pas connecté.
    while (count > 0 && !drap) {
        // On essaye de se connecter
        if (connect(sock, (SOCKADDR*) & sin, sizeof (sin)) != SOCKET_ERROR) {
            printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            drap = true;
        }// En cas d'échec, on réessaye !
        else {
            printf("Impossible de se connecter (%d essai(s) restants)\n", count);
            drap = false;
            count--;
            if (count != NB_TENTATIVES)
                printf("\nNouvelle tentative en cours...\n");
#if defined (WIN32)
            Sleep(2000); // Si on est sous Windows, on utilise Sleep pour attendre 2000 ms.
#else
            sleep(2); // Si on n'est pas sous Windows, on attend 2 secondes.
#endif

        }
    }
    // Si on a épuisé toutes les tentatives de connexion.
    if (count == 0)
        printf("Erreur : la connexion au serveur n'a pue être établie.\nEtes vous sur d'avoir lancé le serveur ?\n");
    return drap;
}

/**
 *  \brief Envoyer le paquet du client
 *
 *  Envoie le paquet du client au serveur avec le flag spécifié.
 *  \param phase flag a communiquer au serveur
 *  \warning le cast du paquet en char* est necessaire pour Windows.
 *  \see enum phasePartie
 */
void LClient::envoyer(phasePartie phase) {

    monPaquet.flag = phase;
    if (send(sock, (char*) &monPaquet, sizeof (monPaquet), 0) != SOCKET_ERROR) {
        this->dbg << " - Paquet envoyé au serveur.";
        o();
    }
}

/**
 *  \brief Recevoir le paquet du serveur
 *
 *  Recoit son paquet du serveur
 *  \warning le cast du paquet en char* est necessaire pour Windows.
 */
int LClient::recevoir() {

    int sock_err = recv(sock, (char*) &monPaquet, sizeof (monPaquet), 0);
    if (sock_err != SOCKET_ERROR) {
        this->dbg << " - Paquet recu du serveur.";
        o();
    }
    return sock_err;
}

/**
 * \brief crée un thread de reception et attend la fin de son exec
 */
void LClient::recevoirTh() {
    pthread_create(&threadClient,NULL, th_recevoir, this);
    pthread_join(threadClient,NULL);
}

/**
 *  \brief Fermer la socket
 *
 *  Ferme la socket du client
 */
void LClient::fermer() {
    closesocket(sock);

#if defined (WIN32)
    WSACleanup(); /// Necessaire pour Windows.
#endif
}

/**
 *  \brief S'identifier aupres du serveur
 *
 *  Determine si on est l'administrateur de la partie (premier connecté) ou juste un joueur.
 *  Le client s'identifie avec identifJoueur() puis, dans le cas ou il est le premier
 *  connecté, il parametre le serveur.
 *  \see LClient::identifJoueur()
 */
void LClient::aquerirStatut() {
    if (monPaquet.flag == ATTENTE_ADMIN) {
        identifJoueur();
        char nomServ[20];
        int nbJs = 0;
        printf("vous êtes le premier connecté.\n");
        printf("vous (%s) êtes l'administrateur de la partie\n\n", monPaquet.pseudo);
        printf("\tCONFIGURATION\n");
        printf("\tNom de la partie : ");
        fgets(nomServ, 20, stdin);  // permet une saisie sécurisée avec prise en compte des espaces.
        this->delRetChar(nomServ);
        bool ok = false;
        while (!ok) {
            printf("\n\tNombre de joueurs : ");
            cin >> nbJs;            // rentrer un caractère / une chaine fera planter le serveur.
            if (nbJs <= 1) {
                cout << "il faut au minimum deux joueurs." << endl << flush;
            } else
                ok = true;
        }
        printf("\nLa partie commencera lorsque %d joueurs auront rejoint la partie...\n", nbJs);
        strcpy(monPaquet.nomPartie, nomServ);
        monPaquet.nbJoueurs = nbJs;

        this->dbg << " - Informations de configuration (" << monPaquet.nomPartie
                << " pour " << monPaquet.nbJoueurs
                << " joueurs) transmises au serveur.";
        o();

    } else if (monPaquet.flag == ATTENTE_JOUEURS) {
        identifJoueur();
    }
}

/**
 * \brief version Qt de aquerirStatut()
 */
bool LClient::aquerirStatutSpecifique(string _nomPartie, int _nbJoueurs) {
    nomPartie=_nomPartie;
    nbJoueurs=_nbJoueurs;
    strcpy(monPaquet.nomPartie, nomPartie.c_str());
    monPaquet.nbJoueurs = nbJoueurs;
    return true;
}

/**
 *  \brief Retourne le flag
 *
 *  Retourne monPaquet.flag, c'est a dire le flag contenu dans le paquet du client.
 *  \see enum phasePartie
 */
phasePartie LClient::gameFlag() {
    return monPaquet.flag;
}

/**
 *  \brief Attend tant qu'on a pas recu le flag en parametre
 *
 *  Apelle LClient::recevoir() tant que le flag donné en paramètre est différent
 *  du flag envoyé par le serveur.
 *  \warning cette methode n'est pas threadée, elle est donc bloquante pour le programme.
 *  \see enum phasePartie
 */
void LClient::attendre(phasePartie flag) {
    while (gameFlag() != flag) {
        recevoir();
    }
}

/**
 *  \brief Recupère le pseudo du joueur
 *
 *  Capture le pseudo du joueur au moyen d'une saisie sécurisée.
 */
void LClient::identifJoueur() {
    char tempPseudo[20];
    printf("Bienvenue !\nEntrez votre pseudo : ");
    fgets(tempPseudo, 20, stdin);
    this->delRetChar(tempPseudo);
    strcpy(monPaquet.pseudo, tempPseudo);
    printf("\n");
}

/**
 *  \brief Affiche les infos de configuration du serveur
 *
 */
void LClient::afficherInfosServeur() {
    cout << "serveur " << monPaquet.nomPartie << " configuré pour " << monPaquet.nbJoueurs << " joueurs." << endl;
}

/**
 *  \brief Interprete le flag recu du serveur
 *
 *  Recoit un paquet du serveur et agit en consequence.
 *  A priori, le serveur peut :
 * \li demander au client de parier.
 * \li envoyer un message.
 * \li communiquer le lancer de dés au client.
 * \li afficher les résultats de la manche.
 * \li déclarer que la partie est terminée.
 * Cette methode entre dans un boucle et n'en sort qu'a la fin de la partie.
 * Elle est donc la clef de voute de la classe client.
 * \see LClient::parier()
 */
void LClient::interpreter() {
    while (!fin_partie) {
        this->recevoir();
        switch (monPaquet.flag) {
            case D_PARI:
                this->dbg << " - demande de pari de la part du serveur. Traitement...\n";
                o();
                cout << "C'est a vous de parier. Entrez le nombre de des, puis leur valeur." << endl;
                this->parier(); // parier() envoye lui même la confirmation au serveur, elle n'est donc pas necessaire.
                break;
            case _MSG:
                this->dbg << " - message a afficher :";
                o();
                printf("%s", monPaquet.msg);
                this->envoyer(OK);
                break;
            case LANCER:
                this->dbg << " - le serveur a envoyé votre lancer.";
                o();
                cout << "Votre lancer de dé : ";
                this->afficherLancer();
                this->envoyer(OK);
                break;
            case RESULT:
                this->dbg << " - la manche est terminée. Le serveur communique les resultats.";
                o();
                cout << "fin de la manche :" << endl << monPaquet.msg << endl;
                break;
            case N_MANCHE:
                this->dbg << " - Nouvelle manche. Paris réinitialisés";
                o();
                cout << "nouvelle manche." << endl;
                monPaquet.pari_face_de = 0;
                monPaquet.pari_nb_de = 0;
                this->envoyer(OK);
                break;
            case FIN_PARTIE:
                this->dbg << " - Fin de la partie. Le serveur communique les resultats.";
                o();
                printf("fin de la partie.\n");
                this->envoyer(OK);
                fin_partie = true;
                break;
        }

    }
}

/**
 *\brief version Qt de interpreter()
 */
int LClient::interpreterSpecifique() {

        switch (monPaquet.flag) {
        case D_PARI:
            this->dbg << " - demande de pari de la part du serveur. Traitement...\n";
            o();
            cout << "C'est a vous de parier. Entrez le nombre de des, puis leur valeur." << endl;
            //this->parier(); // parier() envoye lui même la confirmation au serveur, elle n'est donc pas necessaire.
            retour=1;
            break;
        case _MSG:
            this->dbg << " - message a afficher :";
            o();
            printf("%s", monPaquet.msg);
            this->envoyer(OK);
            retour=2;
            //this->interpreterSpecifique();
            break;
        case LANCER:
            this->dbg << " - le serveur a envoyé votre lancer.";
            o();
            cout << "Votre lancer de dé : ";
            this->afficherLancer();
            this->envoyer(OK);
            retour=3;
            this->interpreterSpecifique();
            break;
        case RESULT:
            this->dbg << " - la manche est terminée. Le serveur communique les resultats.";
            o();
            cout << "fin de la manche :" << endl << monPaquet.msg << endl;
            retour=4;
            this->interpreterSpecifique();
            break;
        case N_MANCHE:
            this->dbg << " - Nouvelle manche. Paris réinitialisés";
            o();
            cout << "nouvelle manche." << endl;
            monPaquet.pari_face_de = 0;
            monPaquet.pari_nb_de = 0;
            retour=5;
            this->envoyer(OK);
            this->interpreterSpecifique();
            break;
        case FIN_PARTIE:
            this->dbg << " - Fin de la partie. Le serveur communique les resultats.";
            o();
            printf("fin de la partie.\n");
            retour=6;
            this->envoyer(OK);
            fin_partie = true;
            break;
        case OK:
            retour=7;
            break;
        case ERR_PARI:
            retour=7;
            break;
        }
        return retour;

}

/**
 *  \brief Récupère le pari
 *
 *  Capture le nombre de dés et la valeur du pari, puis l'envoie au serveur
 *  avec le flag R_PARI (retour pari)
 *  il attend ensuite le retour du serveur qui va confirmer si le pari est valide ou non.
 *  Si il est invalide, on apelle a nouveau la methode parier().
 *  \see LClient::attendreVerifPari()
 */
void LClient::parier() {
    int nb, val;
    cout << "Je parie qu'il y a ";
    cin >> nb;
    cout << "Dés de valeur ";
    cin >> val;
    cout << endl;
    this->dbg << " - paris entrés par l'utilisateur";
    o();
    monPaquet.pari_face_de = val;
    monPaquet.pari_nb_de = nb;
    envoyer(R_PARI);
    if (!attendreVerifPari())
        this->parier(); // power of recursive !!! (fifou dans l'âme)
    else
        cout << "Votre pari est bon !" << endl;
}

/**
 *\brief version Qt de parier();
 */
int LClient::parierSpecifique(int nbDes, int faceDes) {
    int retour = 0;
    monPaquet.pari_face_de = faceDes;
    monPaquet.pari_nb_de = nbDes;
    envoyer(R_PARI);
    if (!attendreVerifPari())
        retour=0;
    else
        retour=1;
    return retour;
}

/**
 *  \brief Attend que le serveur valide ou non le pari
 *
 *  Recoit le paquet du serveur. En fonction du flag donné par ce dernier,
 *  le client sait si son pari est valide ou non.
 *  \return true si le pari est valide, false dans le cas contraire.
 *  \see enum phasePartie
 */
bool LClient::attendreVerifPari() {
    recevoir();
    if (monPaquet.flag == OK) {
        this->dbg << " - le pari est bon.";
        o();
        return true;
    } else if (monPaquet.flag == ERR_PARI) {
        this->dbg << " - le pari est faux.";
        o();
        cout << "votre pari est invalide. réessayez ! :D" << endl;
        return false;
    } else {
        cout << "erreur reception confirmation pari. désynchronisé." << endl;
        this->dbg << " - monPaquet.flag = " << monPaquet.flag;
        o();
        return false;
    }
}

/**
 * \brief Affiche le lancer de dés.
 *
 * Affiche les dés qu'il reste au client.
 */
void LClient::afficherLancer() {
    for (int i = 0; i < monPaquet.nbDes; i++)
        cout << "[" << monPaquet.lancer[i] << "] ";
    cout << endl;
}

/**
  * \brief Retourne le port du client
  */
int LClient::getPort() {
    return port;
}

/**
 * \brief retourne un pointeur sur la premier case du lancer de dés du joueur.
 * @return pointeur sur le tableau du lancer de dés.
 */
int* LClient::getDes() {
    return monPaquet.lancer;
}

/**
  * \brief Retourne le message recu du serveur
  */
string LClient::getMsg() {
    return monPaquet.msg;
}

/**
  * \brief fixe la valeur de l'attribut adresse
  */
void LClient::setAdresse(string _adresse) {
    adresse=_adresse;
}

/**
 * \brief mutateur de inter
 * \deprecated inter n'est plus utilisé.
 * @param _inter
 */
void LClient::setInter(int _inter) {
    inter = _inter;
}

/**
 * \brief accesseur de inter
 * \deprecated inter n'est plus utilisé.
 * \return inter
 */
int LClient::getInter() {
    return inter;
}

/**
  * \brief fixe la veleur de l'attribut port
  */
void LClient::setPort(int _port) {
    port=_port;
}

/**
 * \brief retourne le pseudo du joueur
 */
string LClient::getPseudo() {
    return monPaquet.pseudo;
}

/**
 * \brief retourne fin_partie
 * \return true ou false
 */
bool LClient::isFinPartie() {
    return fin_partie;
}

/**
  *\brief Connexion pour Qt
  * Méthode strictement identique a configurerConnexion(), au détail qu'elle ne prend non pas
  * les arguments de la console en parametre mais un string pour l'adresse et un int pour le port.
  */
void LClient::configurerConnexionSpecifique(string _adresse, int _port) {
    if(_adresse.empty())
        adresse="127.0.0.1";
    else
        adresse=_adresse;
    if(_port==0)
        port=DEF_PORT;
    else
        port=_port;
}

/**
 * \brief vérifie que le serveur est bien paramétré
 * @return true si le serveur est bien paramétré, false sinon
 */
bool LClient::configure() {
    bool ret = false;
    if(nbJoueurs != 0) {
        if(nomPartie != "") {
            ret = true;
        }
        else
            ret = false;
    }
    else
        ret = false;
    return ret;
}

/**
 * \brief accesseur du nom de la partie
 * @return le nom de la partie
 */
string LClient::getNomPartie() {
    return nomPartie;
}

/**
 * \brief mutateur pour le pseudo du joueur
 * @param _pseudo pseudo du joueur
 */
void LClient::setPseudo(string _pseudo) {
    strcpy(monPaquet.pseudo,_pseudo.c_str());
}

/**
 * \brief retourne le nom de la partie contenu dans le paquet du joueur
 * @return le nom de la partie (paquet)
 */
string LClient::getNomServeur() {
    string nom;
    nom = monPaquet.nomPartie;
    return nom;
}

/**
 * \brief retourn un pointeur sur le mutex du client
 * \deprecated le mutex n'est plus utilisé, il était bloqué indéfiniment.
 * @return un pointeur sur le mutex du client.
 */
pthread_mutex_t* LClient::getMutex() {
    return &mutex;
}

/**
 * \brief accesseur sur le pari précédent (nombre de dés)
 * @return le nombre de dés du pari précédent
 */
int LClient::getNbParPrec() {
    return monPaquet.precPariNbDes;
}

/**
 * \brief accesseur sur le pari précédent (valeur du dé)
 * @return la valeur du pari précédent
 */
int LClient::getValParPrec() {
    return monPaquet.precPariValDes;
}

/**
 * accesseur du nombre de dés du joueur.
 * @return le nombre de dés restant au joueur.
 */
int* LClient::getNbDes() {
    return &monPaquet.nbDes;
}
