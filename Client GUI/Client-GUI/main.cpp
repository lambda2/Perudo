#include <QtGui/QApplication>
#include "mainwindow.hpp"
#include "connecter.hpp"

/**
 * \brief Main du programme
 * Executée en console, on peut choisir entre démarrer l'application :
 * - en mode graphique (par défaut) en rajoutant -g
 * - en mode console en rajoutant -c
 * @param argc nombre d'arguments
 * @param argv parametre(s) (-c pour console, -g pour graphique)
 * @return
 */
int main(int argc, char *argv[])
{
    int mode=0;
    if(argc == 1)
    {
        cout << " + defaut : graphique." << endl;
    }
    else if(argc > 1)
    {
        if(strcmp(argv[1],"-c")==0)
        {
            mode=1;
        }
        else if(strcmp(argv[1],"-g")==0)
        {
            mode=0;
        }
        else
        {
            mode=3;
        }
    }
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    Connecter w;
    LClient client;
    string adresse;
    int port;
    switch(mode)
    {


    case 0:
        w.show();
        break;
    case 1:
        cout << "adresse de connexion : ";
        cin >> adresse;
        cout << endl << "port : ";
        cin >> port;
        cout << "lancement du serveur..." << endl;
        client.configurerConnexionSpecifique(adresse,port);
        client.initialiser();
        if(client.connecter())
        {
            client.recevoir();
            client.aquerirStatut();
            client.envoyer();
            client.recevoir();
            client.attendre(START);
            printf("\n\tla partie a commencée !\n");
            client.interpreter();
        }
        client.fermer();
        break;
        case 3:
        cout << "utilisation : " << argv[0] << " [c] || [g] " << endl;
        break;
    }

    if(mode==0)
        return a.exec();
    else
        return 0;
}
