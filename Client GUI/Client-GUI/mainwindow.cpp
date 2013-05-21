#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/**
 * \brief Constructeur de la classe MainWindow.
 * On crée un timer qui apellera la méthode (ou slot) jouer toute les secondes.
 * @param _client pointeur sur le client précédemment déclaré.
 * @param parent
 */
MainWindow::MainWindow(LClient *_client,QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = _client;
    interpretation=0;
    this->toutAfficher();
    QString pseudo(client->getPseudo().c_str());
    ui->LabelStatut->setText("Bienvenue ");
    nbDes=0;
    nbDes=*client->getNbDes();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(jouer()));
    timer->start(1000);
}


/**
 * \brief Destructeur
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * \brief méthode qui désactive tous les boutons (sauf déconnexion et quitter).
 */
void MainWindow::verrouillerBoutons() {
    ui->BoutonDudo->setEnabled(false);
    ui->BoutonParier->setEnabled(false);
    ui->SpinBoxPariNbDe->setEnabled(false);
    ui->SpinBoxPariValeurDe->setEnabled(false);
}

/**
 * \brief méthode qui active tous les boutons (sauf déconnexion et quitter).
 */
void MainWindow::deverrouillerBoutons() {
    ui->BoutonDudo->setEnabled(true);
    ui->BoutonParier->setEnabled(true);
    ui->SpinBoxPariNbDe->setEnabled(true);
    ui->SpinBoxPariValeurDe->setEnabled(true);
}

/**
 * \brief affiche les dés du joueur.
 * Montre tous les dés du joueur en fonction du nombre qu'il lui en reste
 */
void MainWindow::montrerDes() {
nbDes=*client->getNbDes();
    switch(nbDes) {
    case 1:
        ui->De1->show();
        break;
    case 2:
        ui->De1->show();
        ui->De2->show();
        break;
    case 3:
        ui->De1->show();
        ui->De2->show();
        ui->De3->show();
        break;
    case 4:
        ui->De1->show();
        ui->De2->show();
        ui->De3->show();
        ui->De4->show();
        break;
    case 5:
        ui->De1->show();
        ui->De2->show();
        ui->De3->show();
        ui->De4->show();
        ui->De5->show();
        break;
    }

    ui->LabelMonLancer->show();
}

/**
 * \brief cache tous les dés du joueur.
 */
void MainWindow::cacherDes() {
    ui->De1->hide();
    ui->De2->hide();
    ui->De3->hide();
    ui->De4->hide();
    ui->De5->hide();
    ui->LabelMonLancer->hide();
}

/**
 * \brief Affiche le pari du joueur précédent
 */
void MainWindow::montrerPari() {
    ui->LabelPariJoueur->show();
    ui->PariDeJoueur->show();
    ui->PariNbJoueur->show();
    ui->LabelFois->show();
}

/**
 * \brief Masque le pari du joueur précédent
 */
void MainWindow::cacherPari() {
    ui->LabelPariJoueur->hide();
    ui->PariDeJoueur->hide();
    ui->PariNbJoueur->hide();
    ui->LabelFois->hide();
}

/**
 * \brief Masque tous les widgets (sauf déconnexion et quitter)
 */
void MainWindow::toutCacher() {
    this->verrouillerBoutons();
    this->cacherDes();
    this->cacherPari();
    ui->TextEditInfo->hide();
}

/**
 * \brief Affiche tous les widgets
 */
void MainWindow::toutAfficher() {
    this->deverrouillerBoutons();
    this->montrerDes();
    this->montrerPari();
    ui->TextEditInfo->show();
}

/**
 * \brief actualise la valeur des dés du joueur.
 */
void MainWindow::actualiserDes() {

    int acc=0;
    if(lancer[0] == 0) {
        ui->De1->hide();
        acc++;
    }
    else
        ui->De1->setText(QString::number(lancer[0]));
    if(lancer[1] == 0) {
        ui->De2->hide();
        acc++;
    }
    else
        ui->De2->setText(QString::number(lancer[1]));
    if(lancer[2] == 0) {
        ui->De3->hide();
        acc++;
    }
    else
        ui->De3->setText(QString::number(lancer[2]));
    if(lancer[3] == 0) {
        ui->De4->hide();
        acc++;
    }
    else
        ui->De4->setText(QString::number(lancer[3]));
    if(lancer[4] == 0) {
        ui->De5->hide();
        acc++;
    }
    else
        ui->De5->setText(QString::number(lancer[4]));
    if(acc == 4)
        ui->LabelStatutPari->setText("Palifico");
    else if(acc == 5)
        ui->LabelStatutPari->setText("vous êtes éliminé");
}

/**
 * \brief méthode (ou slot) apellée lors d'un clic sur le bouton parier
 * envoie le pari au serveur, si il est bon, on redemmare le timer et
 * on verouille les boutons de pari, sinon on affiche que le pari est invalide
 * et on attend que le joueur recommence.
 */
void MainWindow::on_BoutonParier_clicked() {
    if(client->parierSpecifique(ui->SpinBoxPariNbDe->value(),ui->SpinBoxPariValeurDe->value())==1) {
        ui->LabelStatut->setText("Pari valide par le serveur.");
        this->toutCacher();
        timer->start(1000);
    }
    else
        ui->LabelStatut->setText("Pari invalide");
}

/**
 * \brief Méthode apellée lors d'un clic sur le bouton quitter
 * Quitte le programme.
 */
void MainWindow::on_BoutonQuitter_clicked() {
    qApp->quit();
}

/**
 * \brief Méthode apellée lors d'un clic sur le bouton deconnexion
 * Ferme la socket du joueur.
 * \bug gèle la fenetre.
 */
void MainWindow::on_BoutonDeconnexion_clicked() {
    client->fermer();
    this->cacherDes();
    this->cacherPari();
    ui->LabelStatut->setText("Vous êtes déconnecté");
}

/**
 * \brief Méthode apellée lors d'un clic sur le bouton dudo
 * identique au slot du bouton parier, sauf que le pari envoyé est de 0 dés
 * de face 0, ce qui équivaut pour le serveur a un dudo.
 */
void MainWindow::on_BoutonDudo_clicked() {
    if(client->parierSpecifique(0,0)==1) {
        ui->LabelStatut->setText("Pari valide par le serveur.");
        this->toutCacher();
        timer->start(1000);
    }
    else
        ui->LabelStatut->setText("Pari invalide");
}


/**
 * \brief méthode principale interagissant avec le serveur.
 * Effectue des actions differentes en fonction de la valeur du flag que le
 * client recoit.
 * \bug gèle la fenetre lorsque ce n'est pas au joueur de parier.
 */
void MainWindow::jouer() {
    QString msg;
    pthread_create(&threadJeu,NULL, th_recevoir,client);
    pthread_join(threadJeu,NULL);
    cout << "recu : flag =" << client->gameFlag() << endl;
    switch (client->gameFlag()) {
        {
        case D_PARI:
            ui->LabelStatut->setText(tr("C'est à vous de parier"));
            this->actualiserPari();
            this->toutAfficher();
            timer->stop();
            break;
        case _MSG:
            msg = client->getMsg().c_str();
            msg.toAscii();
            this->toutAfficher();
            this->actualiserDes();
            ui->TextEditInfo->append(tr(client->getMsg().c_str()));
            client->envoyer(OK);
            break;
        case LANCER:
            ui->LabelStatut->setText(tr("Vous avez recu votre lancer de dés"));
            this->toutAfficher();
            lancer = client->getDes();
            this->actualiserDes();
            client->envoyer(OK);
            break;
        case RESULT:
            ui->LabelStatut->setText(tr("La manche est terminée !"));
            break;
        case N_MANCHE:
            ui->LabelStatut->setText("Nouvelle manche");
            client->envoyer(OK);
            break;
        case FIN_PARTIE:
            ui->LabelStatut->setText("Fin de la partie");
            break;
        default:
            this->toutCacher();
            break;

        }
        this->update();
    }

}

/**
 * \brief accesseur de client
 * @return le pointeur sur l'instance de client donnée en parametre au constructeur
 */
LClient* MainWindow::getClient() {
    return client;
}

/**
 * \brief accesseur d'interprétation
 * @return interpretation
 * \deprecated n'est plus utilisé.
 */
int* MainWindow::getInterpretation() {
    return &interpretation;
}

/**
 * \brief retourne un pointeur sur l'UI courante
 * @return pointeur sur UI
 */
Ui::MainWindow* MainWindow::getUi() {
    return ui;
}

/**
 * \brief actualise les labels de pari du joueur précédent.
 */
void MainWindow::actualiserPari() {
    cout << "valParPrec : " << client->getValParPrec() << " nbPArPrec : " << client->getNbParPrec() << endl;
    if(client->getValParPrec() == -1 && client->getNbParPrec() == -1)
    {
        ui->LabelPariJoueur->setText("Aucun pari a afficher pour l'instant");
        this->cacherPari();
    }
    else
    {
        this->montrerPari();
        ui->PariDeJoueur->setText(QString::number(client->getValParPrec()));
        ui->PariNbJoueur->setText(QString::number(client->getNbParPrec()));
    }
}

//-------------------------------- THREADS -------------------------------------------//

/**
 * \brief thread pour interpreter (plus utiisé)
 * @param p_data un LClient
 * @return NULL
 * \deprecated n'est plus utilisé.
 */
void *th_interpreter(void *p_data) {

    LClient *p_cli = (LClient*) p_data;
    if (p_cli != NULL) {
        p_cli->setInter(p_cli->interpreterSpecifique());
    }

    return NULL;
}

/**
 * \brief fonction threadée qui va effectuer un recv()
 * @param p_data un pointeur sur le LClient passé en parametre au constructeur
 * @return NULL
 */
void *th_recevoir(void *p_data) // on passe une struct cli en parametre
{
    LClient *p_cli = (LClient*) p_data; // on la cast en cli
    if (p_cli != NULL) {
        int end = 0;
        //pthread_mutex_lock(p_cli->getMutex()); // provoque un verouillage infini
        do {

            int sock_err = p_cli->recevoir();

            if (sock_err != SOCKET_ERROR) {
                end = 1;
            }
        } while (!end);
        //pthread_mutex_unlock(p_cli->getMutex());
    }

    return NULL;
}
