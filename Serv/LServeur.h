
#ifndef LSERVEUR_H
#define	LSERVEUR_H

#include "Linker.h"
#include "Gestionnaire.hpp"

/**
 * \class LServeur
 * \brief classe du serveur
 * C'est la classe qui va representer le serveur.
 */
class LServeur : public LDebug{
public:
    LServeur();
    LServeur(const LServeur& orig);
    
    virtual ~LServeur();
    bool amorcer();
    void recevoirPaquet(int id=0);
    void fermer();
    void envoyerPaquet(int id=0,const char* msg="$");
    void attendreAdmin();
    void nouveauClient();
    bool socketOk();
    bool isFirstLogin();
    void configurerPartie(Linker *link);
    void enregistrer(Linker *link, int position);
    void broadcast(char *msg);
    void attenteJoueurs();
    void etatServeur();
    void afficherTab(int index = 0);
    void etatTab(Linker* linker,int limite=1);
    void initialiserServeur();
    void sig_DebutPartie();
    void initialiserJeu();
    void sig_DebutJeu();
    bool serveurConfigure();
    void lancerTousLesDes();
    void envoyerDes();
    void attendre(phasePartie phase=OK);
    void demanderParis(int i);
    void nouvelleManche();
    void jouer();
    int joueurPrecedent() const;
    int joueurSuivant() const;
    void setPort(int _port);

    


private:
    SOCKET sock;
    SOCKADDR_IN sin;
    socklen_t recsize;
    int port;
    string adresse;
    int sock_err;
    int erreur;
    int compteurClient;
    int NB_JR_MAX;
    bool joueurPresent;
    int joueursConnectes;
    char nomDeLaPartie[20];
    int idCourante;
    Linker** tabClient;
    Gestionnaire *Jeu;


};

#endif	/* LSERVEUR_H */

