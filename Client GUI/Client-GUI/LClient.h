#ifndef LCLIENT_H
#define	LCLIENT_H

#include "LDebug.h"

/**
 * \class LClient
 * \brief Classe principale du programme client.
 * La classe LClient permet au client de communiquer avec le
 * serveur et d'interpreter les données recues.
 */
class LClient : public LDebug{
public:
    LClient();
    LClient(const LClient& orig);
    virtual ~LClient();
    void configurerConnexion(int argc, char** argv);
    void configurerConnexionSpecifique(string _adresse, int _port);
    void initialiser();
    bool connecter();
    bool connecterClic();
    void envoyer(phasePartie phase=INDEFINI);
    int recevoir();
    void recevoirTh();
    void fermer();
    void aquerirStatut();
    bool aquerirStatutSpecifique(string _nomPartie, int _nbJoueurs);
    void identifJoueur();
    bool tryConnexion();
    void interpreter();
    int interpreterSpecifique();
    void parier();
    bool attendreVerifPari();
    void afficherLancer();
    int getPort();
    void setAdresse(string _adresse);
    void setPort(int _port);
    void setPseudo(string _pseudo);
    string getPseudo();
    bool configure();
    string getNomPartie();
    phasePartie gameFlag();
    void afficherInfosServeur();
    void attendre(phasePartie flag);
    string getNomServeur();
    bool isFinPartie();
    int *getDes();
    string getMsg();
    void setInter(int _inter);
    int getInter();
    pthread_mutex_t *getMutex();
    int parierSpecifique(int nbDes, int faceDes);
    int getValParPrec();
    int getNbParPrec();
    int *getNbDes();
    
private:
    int erreur;
    SOCKET sock;
    SOCKADDR_IN sin;
    Paquet monPaquet;
    bool fin_partie;
    string adresse;
    int port;
    string nomPartie;
    int nbJoueurs;
    int retour;
    int inter;
    pthread_mutex_t mutex;
    pthread_t threadClient;
};

void *th_recevoir(void *p_data);

#endif	/* LCLIENT_H */

