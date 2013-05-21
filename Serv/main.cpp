/*
 * File:   main.cpp
 * Author: lambda2
 *
 * Created on 5 avril 2011, 23:33
 */

#include <cstdlib>
#include "LServeur.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
    LServeur serveur;
    if(argc == 2) {
       serveur.setPort(atoi(argv[1]));
    }
    if (serveur.amorcer()) {
        serveur.attendreAdmin();
    serveur.nouveauClient();
    //serveur.recevoirPaquet();
    cout << "normalement, le serveur devrait être bon... ON VERIFIE !" << endl;
    serveur.etatServeur();
    serveur.sig_DebutPartie();
    serveur.initialiserJeu();
    serveur.jouer();
    }
    

    serveur.fermer();

    return 0;
}
