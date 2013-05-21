#include "connecter.hpp"
#include "ui_connecter.h"

/**
 * \brief Constructeur
 * @param parent
 */
Connecter::Connecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connecter)
{
    ui->setupUi(this);
    client = new LClient;
    ui->SpinBoxPort->setValue(client->getPort());


}

/**
 * \brief Destructeur
 */
Connecter::~Connecter()
{
    delete ui;
}

/**
 * \brief signal déclenché par un clic sur le bouton connecter
 * C'est le signal déclenché par un clic sur le bouton connecter.
 * Il se connecte avec l'adresse et le port donné par le client et ouvre
 * une fenetre de configuration si le joueur est le premier connecté, sinon il
 * ouvre une fenetre d'identification.
 * @return
 */
bool Connecter::on_BoutonConnexion_clicked() {
    client->configurerConnexionSpecifique(ui->LineEditAdresse->text().toStdString(),ui->SpinBoxPort->value());
    client->initialiser();
    bool ret = client->connecterClic();
    if(ret){
        ui->LabelConnexion->setText("Connecté !");
        ui->BoutonConnexion->setEnabled(false);
        client->recevoir();
        if(client->gameFlag() == ATTENTE_ADMIN) {
            config = new Configuration(client);
            config->show();
            this->close();
        }
        else if (client->gameFlag() == ATTENTE_JOUEURS) {
            identif = new Identification(client);
            identif->show();
            this->close();
        }
    }
    else
        ui->LabelConnexion->setText("Echec de la connexion");

    return ret;
}

/**
 * \brief un clic sur le bouton quitter ferme l'application
 */
void Connecter::on_BoutonQuitter_clicked() {
    qApp->quit();
}

