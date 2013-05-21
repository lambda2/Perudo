/*
 * File:   Gestionnaire.cpp
 * Author: lambda2
 *
 * Created on 7 avril 2011, 22:24
 */

 /**
 * \file Gestionnaire.cpp
 * \brief Classe établissant toutes les règles et le déroulement d'un partie.
 * La classe Gestionnaire indique au serveur le déroulement de la partie et
 * gère les vérifications de paris, ainsi que le résultat des manches.
 * \author Aubin.A
 * \version 1.0
 * \date 7 avril 2011, 22:34
 * 
 */
 
#include "Gestionnaire.hpp"

/**
 * \brief Constructeur
 * 
 * Constructeur de la classe Gestionnaire
 * 
 */
Gestionnaire::Gestionnaire(Linker** tabCli, int NB_JR) {
    NB_JR_MAX = NB_JR;
    tabClient = tabCli;
    idDepart = 0;
    idCourante = 0;
    dernierGagnant = -1;
    debut = true;
    this->allouerTableau();
    this->initialiserTableau();
    this->initialiserJoueurs();

}

/**
 * \brief Constructeur de copie
 * 
 * Constructeur de copie de la classe Gestionnaire
 * 
 */
Gestionnaire::Gestionnaire(const Gestionnaire& orig) {

}

/**
 * \brief Destructeur
 * 
 * Destructeur de la classe Gestionnaire
 * 
 */
Gestionnaire::~Gestionnaire() {
    tabClient = NULL;
    this->libererTableau();
}

/**
 * \brief Tableau accueillant les joueurs
 * 
 * Allocation du tableau qui accueillera les joueurs
 * 
 */
void Gestionnaire::allouerTableau() {
    int nColonnes = 7;
    int nLignes = NB_JR_MAX + 1;
    scores = new int* [ nLignes ];
    for (int i = 0; i < nLignes; i++)
        scores[i] = new int[ nColonnes ];
}

/**
 * \brief initialisation du tableau
 * 
 * Initialise le tableau avant le début de la partie
 * 
 */
void Gestionnaire::initialiserTableau() {
    int nColonnes = 7;
    int nLignes = NB_JR_MAX + 1;
    for (int i = 0; i < nLignes; i++)
        for (int j = 0; j < nColonnes; j++)
            scores[i][j] = 0;
}

/**
 * \brief Vidage du tableau
 * 
 * Vide le tableau a la fin de la partie
 * 
 */
void Gestionnaire::libererTableau() {
    for (int i = 0; i < NB_JR_MAX + 1; i++)
        delete[] scores[i];
    delete[] scores;
}

/**
 * \brief Intégrer le joueur a la partie
 * 
 * Intègre le joueur dans le tableau, indiquant qu'il est rentré dans la partie
 * \see Linker::reintegrer()
 * 
 */
void Gestionnaire::initialiserJoueurs() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->reintegrer();
    }
}

/**
 * \brief Demande au joueur de parier
 * 
 * Demande au joueur de faire leur pari chacun leur tour
 * \param id identifiant du joueur faisant le pari
 */
void Gestionnaire::demanderParis(int id) {
    tabClient[id]->newThreadEnvoi("Faites votre pari !");
    pthread_join(tabClient[id]->getThread(), NULL);
}

/**
 * \brief Recoit les paris
 * 
 * Recoit les paris de chaque joueur
 * \param id identifiant du joueur ayant fait le pari
 */
void Gestionnaire::recevoirParis(int id) {
    tabClient[id]->newThreadRecept();
    pthread_join(tabClient[id]->getThread(), NULL);
}

/**
 * \deprecated ne sert a rien
 */
void Gestionnaire::phase_one() {
    printf("vous avez recu votre lancer de des. (ceci est une phrase de politesse)\n");
}

/**
 * \brief Méthode principale de la classe Gestionnaire.
 * Cette méthode entre dans une boucle, a l'interieur de laquelle on vérifie
 * que le pari est bon, et incrémente l'attribut "idCourante", qui représente
 * l'id du joueur actuel si c'est le cas.
 * On sort de la boucle a la fin de chaque manche, et on affiche les resultats.
 * @return true si la partie est terminée.
 */
bool Gestionnaire::phase_two() {
    fin_phase = false;
    fin_tour = false;
    isPalifico = false;
    dernierPerdant = 0;
    idDepart = dernierGagnant;
    paco = false;
    premJoueurManche = true;
    bool pari = true;
    this->palifico();
    this->initialiserTableau();
    while (!fin_tour) {

        this->checkJoueurs();
        if (fin_tour && fin_phase) {
            cout << endl << endl << "      FIN DE LA PARTIE     " << endl << endl;
        } else if (tabClient[idCourante]->isAlive()) {
            if (pari) {
                if (!debut)
                    this->suiviPartie(joueurPrecedent(idCourante));
                tabClient[idCourante]->pari();

            }

            tabClient[idCourante]->attendre(R_PARI);
            if (idCourante == 0
                    && debut
                    && verifierLimitePari()
                    && tabClient[idCourante]->getPariFaceDe() != 1
                    && tabClient[idCourante]->getPariFaceDe() != 0
                    && tabClient[idCourante]->getPariNbDes() != 0
                    && verifierPariPalifico()) {
                printf("debut de la partie !\n");
                afficherPari();
                debut = false;
                idCourante++;
                pari = true;
            } else if (verifierLimitePari()
                    && verifierPari()
                    && !debut
                    && verifierPariPalifico()) {
                afficherPari();
                menteur();
                idCourante = joueurSuivant(idCourante);
                pari = true;
            } else if (premJoueurManche
                    && verifierLimitePari()
                    && verifierPari()
                    && !debut) {
                afficherPari();
                menteur();
                idCourante = joueurSuivant(idCourante);
                pari = true;
            } else {
                cout << endl << "\t-------------------------------------------------"
                        << endl << "\tPari invalide ! Veuillez reformuler votre pari"
                        << endl << "\t-------------------------------------------------"
                        << endl;
                pari = false;
                this->afficherParisDBG();
            }
            if (pari) {
                this->enregistrerPariPrecedent(idCourante);
                tabClient[joueurPrecedent(idCourante)]->envoyerPariBon();
                premJoueurManche = false;
            } else
                tabClient[idCourante]->envoyerPariPasBon();

        } else {
            this->eliminerJoueur(idCourante);
            idCourante = joueurSuivant(idCourante);

        }
    }
    this->resumeManche(dernierGagnant);
    cout << endl << "\t-------------------------------------------------"
            << endl << "\t\tNOUVELLE MANCHE !"
            << endl << "\t-------------------------------------------------"
            << endl;
    this->afficherParisDBG();
    this->checkJoueurs();
    return fin_phase;

}

/**
 * \brief verifie que le joueur joue toujours
 */
void Gestionnaire::checkJoueurs() {
    cout << "etat de " << tabClient[idCourante]->getLogin() << " = " << tabClient[idCourante]->isAlive() << endl;
    if (tabClient[idCourante]->isAlive()) {
        cout << tabClient[idCourante]->getLogin() << " (id=" << tabClient[idCourante]->getId() << ") est ALIVE !" << endl;
        if (this->finDeLaPartie()) {
            fin_phase = true;
            fin_tour = true;
        }
    } else {
        cout << tabClient[idCourante]->getLogin() << " a perdu. Il ne joue plus." << endl;
        idCourante = joueurSuivant(idCourante);
    }
}

/**
 * \brief annonce au joueurs la fin de la partie.
 */
void Gestionnaire::declarerFinPartie() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        string strMsg = this->msgFinPartie();
        tabClient[i]->setFlag(_MSG);
        tabClient[i]->envoyer(strMsg.c_str());
        tabClient[i]->attendre(OK);
        tabClient[i]->setFlag(FIN_PARTIE);
        tabClient[i]->envoyer();
        tabClient[i]->attendre(OK);
        tabClient[i]->fermerSocket();
    }
}

/**
 * \brief Message de fin
 * 
 * affiche le message de la fin de la partie en indiquant le gagnant
 * \return le message de fin de partie.
 */
string Gestionnaire::msgFinPartie() {
    if (finDeLaPartie()) {
        stringstream message;
        message << "La partie est terminée, merci d'avoir joué. Le gagnant est " << tabClient[getIdGagnant()]->getLogin() << endl;
        return message.str();
    } else {
        return "";
    }
}

/**
 * \brief Obtenir identifiant du gagnant
 * 
 * Va déterminer l'identifiant du gagnant
 * \return acc case possédant l'identifiant du vainqueur
 */
int Gestionnaire::getIdGagnant() {
    if (finDeLaPartie()) {
        int acc = 0;
        for (int i = 0; i < NB_JR_MAX; i++) {
            if (tabClient[i]->getNbDes() > 0)
                acc = i;
        }
        return acc;
    }
}

/**
 * \brief Enregistre le pari du joueur précédent
 *
 * \param id identifiant du joueur précédent
 */
void Gestionnaire::enregistrerPariPrecedent(int id) {
    tabClient[id]->setPariJoueurPrecedent(tabClient[joueurPrecedent(id)]->getPariFaceDe(),tabClient[joueurPrecedent(id)]->getPariNbDes());
}

/**
 * \brief fonction de debug qui affiche l'id, le pari et le lancer de dés des joueurs
 * 
 */
void Gestionnaire::afficherParisDBG() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        cout << "id=" << tabClient[i]->getId() << " -> " << tabClient[i]->getPariNbDes() << " x [" << tabClient[i]->getPariFaceDe() << "]  |  ";
        for (int j = 0; j < 5; j++) //face du dé
        {
            cout << "[" << tabClient[i]->getDe(j) << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * \brief Afficher le pari
 * 
 * Affiche le pari du joueur et déclare aussi si le joueur dit dudo
 * 
 */
void Gestionnaire::afficherPari() const {

    if (tabClient[idCourante]->getPariNbDes() != 0) {
        cout << "le pari de " << tabClient[idCourante]->getLogin() <<
                " (ID=" << tabClient[idCourante]->getId() <<
                ") est que il y a " << tabClient[idCourante]->getPariNbDes() <<
                " de(s) de face " << tabClient[idCourante]->getPariFaceDe() << endl;
    } else {
        cout << tabClient[idCourante]->getLogin() << " (id=" << tabClient[idCourante]->getId() << ") déclare DUDO !" << endl;
    }

}

/**
 * \brief Verification du pari
 * 
 * Verifie si le pari fait par le joueur est correct ou non, dans le cas ou
 * il n'est pas correct, le joueur doit reformuler son pari
 * \return true si le pari est valide
 * 
 */
bool Gestionnaire::verifierPari() {
    if (tabClient[idCourante]->getPariFaceDe() == 0 && tabClient[idCourante]->getPariNbDes() == 0) {
        return true;
    } else if (!paco) {
        if (tabClient[idCourante]->getPariFaceDe() > tabClient[joueurPrecedent(idCourante)]->getPariFaceDe()
                || tabClient[idCourante]->getPariNbDes() > tabClient[joueurPrecedent(idCourante)]->getPariNbDes()) {
            return true;
        } else if (tabClient[idCourante]->getPariFaceDe() == 1
                && tabClient[idCourante]->getPariNbDes() > (tabClient[joueurPrecedent(idCourante)]->getPariNbDes()) / 2) {
            cout << "pari valide car" << tabClient[idCourante]->getPariNbDes() <<
                    "des paco sont superieurs a " << (tabClient[joueurPrecedent(idCourante)]->getPariNbDes()) / 2 <<
                    "(" << tabClient[joueurPrecedent(idCourante)]->getPariNbDes() << "/2)" << endl;
            paco = true;
            return true;
        }


    } else if (paco) {
        if (tabClient[idCourante]->getPariNbDes() > tabClient[joueurPrecedent(idCourante)]->getPariNbDes()
                && tabClient[idCourante]->getPariFaceDe() == 1) {
            return true;
        } else if (tabClient[idCourante]->getPariNbDes() > (tabClient[joueurPrecedent(idCourante)]->getPariNbDes())*2
                && tabClient[joueurPrecedent(idCourante)]->getPariFaceDe() == 1) {
            cout << "pari valide car" << tabClient[idCourante]->getPariNbDes() <<
                    "des paco sont superieurs a " << (tabClient[joueurPrecedent(idCourante)]->getPariNbDes()) * 2 <<
                    "(" << tabClient[joueurPrecedent(idCourante)]->getPariNbDes() << "*2)" << endl;
            paco = false;
            return true;
        }
    }
    cout << "le pari n'a pas été vérifié dans verifierPari()" << endl;
    return false;

}

/**
 * \brief Déclaration de menteur
 * 
 * Le joueur a annoncer DUDO, on affiche les résultats, on détermine qui a raison
 * et on commence un nouveau tour.
 * \see afficherResultats()
 */
void Gestionnaire::menteur() {
    if (tabClient[idCourante]->getPariFaceDe() == 0 && tabClient[idCourante]->getPariNbDes() == 0) {
        cout << endl << tabClient[idCourante]->getLogin() << " dit : menteur" << endl;
        fin_tour = true;
        afficherResultats();
        idDepart = idCourante;
        cout << "\nle pari de " << tabClient[joueurPrecedent(idCourante)]->getLogin() <<
                " est que il y a " << tabClient[joueurPrecedent(idCourante)]->getId() <<
                " de(s) de face " << tabClient[joueurPrecedent(idCourante)]->getPariFaceDe() << endl;
        cout << "\nvotre pari (" << tabClient[idCourante]->getLogin() <<
                ") est que il y a " << tabClient[idCourante]->getId() <<
                " de(s) de face " << tabClient[idCourante]->getPariFaceDe() << endl;
        cout << endl << "Fin du tour!!" << endl << "Et debut d'un nouveau ^^" << endl << endl;
    }
}

/**
 * \brief Afficher résultat
 * 
 * Affiche le résultat a la fin du tour, annonce qui a tort et qui avait raison
 * 
 */
void Gestionnaire::afficherResultats() {
    //afficher les lancers des joueurs
    cout << endl << "Resultats de la manche : " << endl;
    genererScores();
    if (pariVrai(joueurPrecedent(idCourante))) // defaite...
    {
        cout << endl << tabClient[joueurPrecedent(idCourante)]->getLogin() << " (ID=" << tabClient[joueurPrecedent(idCourante)]->getId() << ")" << " avait raison, vous avez perdu et perdez un de !" << endl;
        tabClient[idCourante]->enleverDes();
        dernierGagnant = tabClient[joueurPrecedent(idCourante)]->getId();
    } else // victoiiiire !
    {
        cout << endl << tabClient[joueurPrecedent(idCourante)]->getLogin() << " (ID=" << tabClient[joueurPrecedent(idCourante)]->getId() << ")" << " avait tort, vous avez gagne et il perd un de !" << endl;
        tabClient[joueurPrecedent(idCourante)]->enleverDes();
        dernierGagnant = tabClient[idCourante]->getId();
    }
}

/**
 * \brief Resume de la manche
 * 
 * Affiche les résultats de la manche, fait un récapitulatif des dés en jeu 
 * et annonce qui gagne/perd un dé
 * \param idGagnante identifiant du vainqueur de la manche
 */
void Gestionnaire::resumeManche(int idGagnante) {
    if (idGagnante >= 0 && idGagnante < NB_JR_MAX) {
        stringstream resManche;
        for (int i = 0; i < NB_JR_MAX; i++) {
            resManche.str("");
            string strManche = "";
            resManche << " 1 | 2 | 3 | 4 | 5 | 6" << endl;
            resManche << " ---------------------" << endl;
            for (int k = 0; k <= NB_JR_MAX; k++) {
                for (int j = 0; j < 6; j++) {
                    resManche << "[" << scores[k][j] << "] ";
                }
                resManche << endl;
            }
            if (i == joueurPrecedent(idGagnante)) // defaite...
            {
                resManche << endl << tabClient[joueurPrecedent(i)]->getLogin() << "(ID=" << tabClient[joueurPrecedent(i)]->getId() << ")" << " avait raison, vous avez perdu et perdez un de !" << endl;
            } else if (i == idGagnante)// victoiiiire !
            {
                resManche << endl << tabClient[joueurPrecedent(i)]->getLogin() << "(ID=" << tabClient[joueurPrecedent(i)]->getId() << ")" << " avait tort, vous avez gagne et il perd un de !" << endl;
            } else {
                cout << endl << tabClient[idGagnante]->getLogin() << "(ID=" << tabClient[idGagnante]->getId() << ")" << " avait tort, vous avez gagne et il perd un de !" << endl;
            }

            strManche = resManche.str();
            tabClient[i]->setFlag(RESULT);
            dbg << "  - la chaine de caracteres strManche a une longueur de " << strManche.length();
            o();
            int envoi = tabClient[i]->envoyer(strManche.c_str());
            if (envoi != SOCKET_ERROR)
                dbg << "  - resultats de la manche envoyés à " << tabClient[i]->getLogin();
            else
                dbg << "  - echec de l'envoi pour " << tabClient[i]->getLogin();
            o();
        }

    }
}

/**
 * \brief Identifier le joueur précédent par rapport a i (parametre)
 * 
 * \param i id de référence
 * \return id identifiant du joueur précédent 
 * 
 */
int Gestionnaire::joueurPrecedent(int i) const {
    int id = 0;
    if (i == 0)
        id = NB_JR_MAX - 1;
    else
        id = i - 1;
    return id;
}

/**
 * \brief Identifier le joueur suivant par rapport a i (parametre)
 * 
 * \param i id de référence
 * \return id identifiant du joueur suivant
 *  
 */
int Gestionnaire::joueurSuivant(int i) const {
    int id = 0;
    if (i == NB_JR_MAX - 1)
        id = 0;
    else
        id = i + 1;
    return id;
}

/**
 * \brief Verifier la limite du pari
 * 
 * Permet de vérifier qu'un joueur annonce une face de dé supérieur a 6 
 * ainsi qu'un nombre de dé supérieur au nombre total de dé en jeu
 * \return true ou false
 * 
 */
bool Gestionnaire::verifierLimitePari() const
//verifier qu'on ne puisse faire de pari excedant la limite du dé
{
    if (tabClient[idCourante]->getPariFaceDe() == 0
            && tabClient[idCourante]->getPariNbDes() == 0) {
        cout << "!!! Limite verifiee !!!" << endl;
        return true;
    } else if (tabClient[idCourante]->getPariFaceDe() <= 6
            && tabClient[idCourante]->getPariFaceDe() > 0
            && tabClient[idCourante]->getPariNbDes() > 0
            && tabClient[idCourante]->getPariNbDes() <= 5 * NB_JR_MAX) {
        cout << "!!! Limite verifiee !!!" << endl;
        return true;
    } else {
        cout << "!!! LIMITE FAUSSE !!!" << endl;
        cout << "le pari n'a pas été vérifié dans verifierLimitePari()" << endl;
        return false;
    }

}

/**
 * \brief Générer les scores
 * 
 * Génère le tableau des scores a la fin de chaque manche avec le récapitulatif
 * des dés de chaque joueur et le nombre de dés de chaque face total
 * \param afficher
 * \see afficherTabScores()
 * 
 */
void Gestionnaire::genererScores(bool afficher)
//generer le tableau des scores
{
    /* Met à zéro toute la zone mémoire */
    int totalPaco = 0;
    if (afficher) {
        cout << " -----------------------------------------" << endl;
        cout << "  ID  | [1] | [2] | [3] | [4] | [5] | [6] " << endl;
        cout << " -----------------------------------------" << endl;
    }
    for (int i = 0; i < NB_JR_MAX; i++) // on parcours les ID joueurs
    {
        if (afficher) cout << "   " << i << "  ";
        int *lancer = tabClient[i]->getLancer();
        for (int j = 1; j <= 6; j++)//face du dé
        {
            for (int k = 0; k < tabClient[idCourante]->getNbDes(); k++) // dé n°
            {

                if (lancer[k] == j) {
                    scores[i][j - 1]++;
                }
            }
            if (afficher) cout << "|  " << scores[i][j - 1] << "  ";
        }
        if (afficher) cout << endl;
    }
    if (afficher) cout << " -----------------------------------------" << endl;
    if (afficher) cout << "TOTAL";


    for (int j = 1; j <= 6; j++)//face du dé
    {
        for (int i = 0; i < NB_JR_MAX; i++) // on parcours les ID joueurs
        {
            scores[NB_JR_MAX][j - 1] += scores[i][j - 1];
        }
        if (afficher) printf("   %d  ", scores[NB_JR_MAX][j - 1]);
    }
    totalPaco = scores[NB_JR_MAX][0];
    for (int i = 1; i < 6; i++) {
        scores[NB_JR_MAX][i] += totalPaco;
    }
    afficherTabScores();
}

/**
 * \brief verifie (en fonction du tableau des scores) que le pari du joueur est vrai
 *
 * \param idJoueur id du joueur
 * \return true si le pari est vrai
 *  
 */
bool Gestionnaire::pariVrai(int idJoueur) {
    if (scoresVide()) {
        genererScores(false);
        cout << "scores generes" << endl;
    }
    if (scores[NB_JR_MAX][tabClient[idJoueur]->getPariFaceDe() - 1] >= tabClient[idJoueur]->getPariNbDes()) {
        return true;
    } else {
        return false;
    }
}

/**
 * \brief regarde si le tableau des scores est vide
 *
 * \return true si le tableau est vide
 *  
 */
bool Gestionnaire::scoresVide() const {
    bool vide = true;
    for (int i = 0; i < 6; i++) {
        if (scores[NB_JR_MAX][i] != 0)
            vide = false;
    }
    return vide;
}

/**
 * \brief affiche le tableau des scores
 * 
 */
void Gestionnaire::afficherTabScores() {
    cout << endl;
    for (int i = 0; i <= NB_JR_MAX; i++) {
        for (int j = 0; j < 6; j++) {
            cout << " [" << scores[i][j] << "] ";
        }
        cout << endl;
    }
}

/**
 * \brief Enlever un dé
 * 
 * Enlève un dé au joueur qui a perdu la manche
 * \param client 
 * 
 */
void Gestionnaire::enleverDe(Paquet* client)
{
    switch (client->nbDes) {
        case 2:
            client->nbDes = client->nbDes - 1;
            client->lancer[client->nbDes + 1] = 0;
            cout << "Le joueur " << client->pseudo << " n'a plus qu'un de, on rentre dans un tour de Palifico!!! =D " << endl;
            break;
        case 1:
            cout << "Le joueur " << client->pseudo << " n'a plus de des, vous etes le maillon faible, au revoir!" << endl;

            break;
        default:
            client->nbDes = client->nbDes - 1;
            client->lancer[client->nbDes + 1] = 0;
            cout << "Le joueur " << client->pseudo << " vient de perdre un de, il lui en reste encore " << client->nbDes << endl;
            break;
    }
}

/**
 * \brief Déterminer la fin de la partie
 * 
 * \return true si c'est la fin de la partie
 * 
 */
bool Gestionnaire::finDeLaPartie() {
    int acc = 0;
    for (int i = 0; i < NB_JR_MAX; i++) {
        if (tabClient[i]->getNbDes() > 0)
            acc++;
    }

    if (acc == 1) {
        return true;
    } else
        return false;
}

/**
 * \brief Lancer les dés
 * 
 * Lance les dés de manière aléatoire pour chaque joueur
 * \param paquetJoueur un pointeur sur le paquet a modifier
 * 
 */
void lancerDes(Paquet *paquetJoueur) {
    memset(paquetJoueur->lancer, 0, sizeof (paquetJoueur->lancer));
    cout << endl << "Lancer de des : ";
    for (int i = 0; i < paquetJoueur->nbDes; i++) {
        paquetJoueur->lancer[i] = rand() % (6) + 1;
        cout << "[" << paquetJoueur->lancer[i] << "] " << endl;
    }
    cout << endl;
}

/**
 * \brief Déterminer le Palifico
 * 
 * Détermine le moment où un joueur n'a plus qu'un dé afin de lancer un tour
 * de Palifico
 * 
 */
void Gestionnaire::palifico() {
    for (int i = 0; i < NB_JR_MAX; i++) {
        if (tabClient[i]->getNbDes() == 1) {
            isPalifico = true;
            cout << "le joueur " << tabClient[i]->getLogin() << " n'a plus qu'un dé. Palifico !" << endl;
        }
    }
}

/**
 * \brief Verifier le pari lors du Palifico
 * 
 * Vérifie si les paris des joueurs lors des tours de Palifico sont bon ou non
 * \return true si le pari est bon
 *  
 */
bool Gestionnaire::verifierPariPalifico() {
    if (isPalifico) {
        if (tabClient[idCourante]->getPariFaceDe() == 0
                && tabClient[idCourante]->getPariNbDes() == 0) {
            return true;
        } else if (tabClient[idCourante]->getPariFaceDe() == tabClient[joueurPrecedent(idCourante)]->getPariFaceDe()
                && tabClient[idCourante]->getPariNbDes() > tabClient[joueurPrecedent(idCourante)]->getPariNbDes()) {
            cout << "Pari valide (Palifico)" << endl;
            return true;
        } else {
            return false;
        }
    } else
        return true;
}

/**
 * \brief envoyer aux clients qui ne jouent pas l'évolution de la partie
 * 
 * \param idExclue identifiant du joueur qui joue
 * 
 */
void Gestionnaire::suiviPartie(int idExclue) {
    stringstream message;
    if (tabClient[idExclue]->isAlive()) {
        message << endl << tabClient[joueurPrecedent(idCourante)]->getLogin() <<
                " a parié";
        if (tabClient[joueurPrecedent(idCourante)]->getPariNbDes() == 0
                && tabClient[joueurPrecedent(idCourante)]->getPariFaceDe() == 0) {
            message << " que le pari précédent (" << tabClient[joueurPrecedent(joueurPrecedent(idCourante))]->getPariNbDes() <<
                    " des de face " << tabClient[joueurPrecedent(joueurPrecedent(idCourante))]->getPariFaceDe() << ") était faux. Dudo !";
        } else {
            message << " qu'il y a " << tabClient[joueurPrecedent(idCourante)]->getPariNbDes() <<
                    " dés de face " << tabClient[joueurPrecedent(idCourante)]->getPariFaceDe();
        }
    } else {
        message << tabClient[idExclue]->getLogin() << " n'a plus de dés, et ne joue donc pas." << endl;
    }
    string strMess = message.str();
    for (int i = 0; i < NB_JR_MAX; i++) {
        if (i != idExclue) {
            tabClient[i]->setFlag(_MSG);
            tabClient[i]->envoyer(strMess.c_str());
            tabClient[i]->attendre(OK);
        }
    }

}

/**
 * \brief Elimine un joueur
 * 
 * Elimine le joueur qui n'a plus de dés a la fin du tour
 * \param id identifiant du joueur ayant perdu
 * 
 */
void Gestionnaire::eliminerJoueur(int id) {
    stringstream messageAutres;
    stringstream messageElimi;

    if (!tabClient[id]->isAlive()) {
        messageAutres << tabClient[id]->getLogin() <<
                " n'a plus de dés. Il a perdu." << endl;
    }
    messageElimi << "vous n'avez plus de dés. Vous avez perdu." << endl;
    string strMessElimi = messageElimi.str();
    string strMessAutres = messageAutres.str();
    for (int i = 0; i < NB_JR_MAX; i++) {
        tabClient[i]->setFlag(_MSG);
        if (i != id) {
            tabClient[i]->newThreadEnvoi(strMessAutres.c_str());
            pthread_join(tabClient[i]->getThread(), NULL);
            tabClient[i]->attendre(OK);
        } else {
            tabClient[i]->newThreadEnvoi(strMessElimi.c_str());
            pthread_join(tabClient[i]->getThread(), NULL);
            tabClient[i]->attendre(OK);
        }
    }
}
