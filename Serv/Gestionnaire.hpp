/* 
 * File:   Gestionnaire.hpp
 * Author: lambda2
 *
 * Created on 7 avril 2011, 22:24
 */

#include <stdio.h>
#include <string.h>
#include "../header.h"
#include "Linker.h"

#ifndef GESTIONNAIRE_HPP
#define	GESTIONNAIRE_HPP

/**
 * \class Gestionnaire
 * \brief Classe établissant toutes les règles et le déroulement d'un partie.
 * La classe Gestionnaire indique au serveur le déroulement de la partie et
 * gère les vérifications de paris, ainsi que le résultat des manches.
 */
class Gestionnaire : public LDebug {
public:
    Gestionnaire(Linker** tabCli, int NB_JR);
    Gestionnaire(const Gestionnaire& orig);
    virtual ~Gestionnaire();
    void allouerTableau();
    void initialiserTableau();
    void libererTableau();
    void phase_one();
    bool phase_two();
    void afficherPari() const; // a ne pas utiliser pour le premier lancer
    bool verifierPari();
    void menteur();
    void afficherResultats();
    int joueurPrecedent(int i) const;
    int joueurSuivant(int i) const;
    bool verifierLimitePari() const;
    void genererScores(bool afficher = true);
    bool pariVrai(int idJoueur); // necessite que le tableau des scores soit établi
    bool scoresVide() const;
    void afficherTabScores();
    void enleverDe(Paquet *Client);
    void rajouterDe(Paquet *Client);
    bool finDeLaPartie();
    void recevoirParis(int id);
    void demanderParis(int id);
    void palifico();
    bool verifierPariPalifico();
    void suiviPartie(int idExclue);
    void resumeManche(int idGagnante);
    void afficherParisDBG();
    void checkJoueurs();
    void initialiserJoueurs();
    void declarerFinPartie();
    string msgFinPartie();
    int getIdGagnant();
    void eliminerJoueur(int id);
    void enregistrerPariPrecedent(int id);


private:
    Linker** tabClient;
    int idDepart;
    int idCourante;
    bool fin_tour;
    bool fin_phase;
    bool debut;
    bool paco;
    int retourServeur;
    int dernierGagnant;
    int dernierPerdant;
    int** scores; //int* scores[NB_JR_MAX+1][6];
    int NB_JR_MAX;
    bool isPalifico;
    bool premJoueurManche;

};



#endif	/* GESTIONNAIRE_HPP */

