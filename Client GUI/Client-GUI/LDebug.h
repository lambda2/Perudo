/* 
 * File:   LDebug.h
 * Author: lambda2
 *
 * Created on 10 mai 2011, 21:37
 */


#include "header.h"

using namespace std;

#ifndef LDEBUG_H
#define	LDEBUG_H

/**
 * \class LDebug
 * \brief Classe de déboguage
 * Cette classe est mère (ou héritée) de la plupart des autres classes
 * pour acceder à ses méthodes de n'importe ou.
 */
class LDebug {
public:
    LDebug();
    LDebug(const LDebug& orig);
    virtual ~LDebug();
    void o();
    void delRetChar(char *chaine);

protected:
    ostringstream dbg;

private:
    ofstream fichier;

};

#endif	/* LDEBUG_H */

