#include "identification.hpp"
#include "ui_identification.h"

/**
 * \brief Constructeur
 * Fenetre demandant le login du joueur.
 * @param _client pointeur sur l'instance de LClient déclarée précédemment
 * @param parent
 */
Identification::Identification(LClient *_client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Identification)
{
    ui->setupUi(this);
    client = _client;
    if(!client->getNomPartie().empty()) {
    QString nomserv = client->getNomPartie().c_str();
    ui->LabelBienvenue->setText(QString("Bienvenue sur " + nomserv));
}
    else
        ui->LabelBienvenue->setText(QString("Bienvenue !"));
}

/**
 * \brief Destructeur
 */
Identification::~Identification()
{
    delete ui;
}

/**
 * \brief signal apellé lors d'un clic sur le bouton valider
 * Lors d'un clic sur le bouton valider, si le champ n'est pas vide,
 * la méthode va envoyer le pseudo au serveur et ouvrir la fenetre principale
 * du jeu.
 */
void Identification::on_BoutonValider_clicked() {
    if(ui->LineEditPseudo->text() != "") {
        client->setPseudo(ui->LineEditPseudo->text().toStdString());
        client->envoyer();
        client->recevoir();
        mainW = new MainWindow(client);
        mainW->show();
        this->close();
    }
    else
        QMessageBox::warning(this, "Erreur", "Vous devez choisir un pseudo");
}
