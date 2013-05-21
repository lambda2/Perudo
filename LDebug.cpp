/**
 *
 * \file LDebug.cpp
 * \brief Classe de déboguage
 * Cette classe est mère (ou héritée) de la plupart des autres classes
 * pour acceder à ses méthodes de n'importe ou.
 * \author Aubin.A
 * \version 1.0
 * \date 10 mai 2011, 21:37
 *
 */

#include "LDebug.h"
#include "Serv/Linker.h"

/**
 * \brief Constructeur
 * Si le debug est activé (constante dans header.h), alors on ouvre / crée le
 * fichier debug.log, qui contiendra l'historique de l'execution du programme.
 */
LDebug::LDebug() {
    if (DEBUG) {
        fichier.open("debug.log", ios::out | ios::app);
        if (fichier)
            fichier << " * debut";
    }
}

/**
 * \brief Constructeur de copie
 * @param orig instance a copier
 */
LDebug::LDebug(const LDebug& orig) {
}

/**
 * \brief Destructeur
 * Si le debug est activé (constante dans header.h), on ferme le fichier que
 * le constructeur a ouvert.
 */
LDebug::~LDebug() {
    if (DEBUG) {
        fichier.close();
    }
}

/**
 * \brief Fonction principale de debogage
 * Si le debug est activé (constante dans header.h), on affiche le contenu du
 * flux dbg et on le place dans le fichier debug.log.
 * Ensuite, on efface le contenu du flux.
 * L'avantage de manipuler des flux est clairement de pouvoir afficher des
 * variables et/ou du texte sans interruption, comme on le ferait pour un cout.
 */
void LDebug::o() {
    if (DEBUG) {
        cout << dbg.str() << endl;
        fichier << dbg.str() << endl;
        dbg.str("");
    }
}

/**
 * \brief supprime le saut de ligne au bout de la chaine donnée en paramètre
 * Cette methode va cherche un saut de ligne (\n) et si il y en a un, le
 * supprimer.
 * @param chaine chaine contenant un saut de ligne.
 */
void LDebug::delRetChar(char* chaine) {
    char *p = strchr(chaine, '\n');

    if (p) {
        *p = 0;
    }
}
