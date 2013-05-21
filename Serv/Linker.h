/* 
 * File:   Linker.h
 * Author: lambda2
 *
 * Created on 16 mai 2011, 16:38
 */

#ifndef LINKER_H
#define	LINKER_H

#include "../LDebug.h"

/**
 * \class Linker
 * \brief 
 */
class Linker : public LDebug{
public:
    Linker();
    Linker(const Linker& orig);
    virtual ~Linker();
    void accepter(SOCKET socket);
    void accepterAdmin(SOCKET socket);
    void newThreadEnvoi(const char* msg="$");
    void newThreadRecept();

    SOCKET getSocket();
    pthread_t getThread();
    int getConfig(char *nom);
    int getNbDes();
    string getLogin();
    int getPariNbDes();
    int getPariFaceDe();
    int getId();
    int *getLancer();
    int getDe(int de);
    pthread_mutex_t *getMutex();
    bool isAlive();

    void setNbDes(int nb);
    void setFlag(phasePartie flag);
    void setId(int _id);
    void setmsg(const char *msg);
    void setRecsize();
    void setPariJoueurPrecedent(int val, int nb);
    void eliminer();
    void reintegrer();

    void lancerDes();
    bool enleverDes();
    void attendre(phasePartie phase=OK);
    void pari();

    void etat();

    void recupererPaquet(Paquet temp);
    void initialiserPaquet();
    int recevoir();
    int envoyer(const char* msg="$");
    void fermerSocket();
    void envoyerPariBon();
    void envoyerPariPasBon();

    friend void *newLinker (Linker *p_data);
    Linker& operator =(const Linker& Other);

private:
    Paquet paquetJoueur;
    pthread_t thread;
    pthread_mutex_t mutex;
    SOCKADDR_IN csin;
    int recsize;
    SOCKET csock;
    bool paquetRecu;
    bool isAdmin;
};

#endif	/* LINKER_H */


void *th_envoyer (void *p_data);
void *th_recevoir (void *p_data);
