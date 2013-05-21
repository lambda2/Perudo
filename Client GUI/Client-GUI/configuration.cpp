#include "configuration.hpp"
#include "ui_configuration.h"

/**
 * \brief constructeur
 */
Configuration::Configuration(LClient *_client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);
    client=_client;
}

/**
 * \brief destructeur
 */
Configuration::~Configuration()
{
    delete ui;

}

/**
 * Méthode apellée lorsque l'on clique sur le bouton valider.
 * Elle vérifie que tous les champs sont remplis et les envoie au Serveur.
 * @return
 */
void Configuration::on_BoutonValider_clicked() {
    if(ui->LineEditNomPartie->text() == "") {
        QMessageBox::warning(this, "Erreur", "Vous devez donner un nom a votre partie !");
    }
    else
    {
        client->aquerirStatutSpecifique(
                ui->LineEditNomPartie->text().toStdString(),
                ui->SpinBoxNbJoueurs->value()
                );
        if(ui->LineEditPseudoAdmin->text() != "") {
            QMovie mov("/res/loading_big.gif");
            ui->Loader->setMovie(&mov);
            mov.start();
            ui->Loader->show();
            client->setPseudo(ui->LineEditPseudoAdmin->text().toStdString());
            client->envoyer();
            client->recevoir();
            mainW = new MainWindow(client);
            mainW->show();
            this->close();
        }
        else
            QMessageBox::warning(this, "Erreur", "Vous devez choisir un pseudo");

    }
}
