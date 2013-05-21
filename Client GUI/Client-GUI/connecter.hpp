#ifndef CONNECTER_HPP
#define CONNECTER_HPP

#include <QDialog>
#include "LClient.h"

#include "configuration.hpp"
#include "identification.hpp"

namespace Ui {
    class Connecter;
}

/**
 * \class Connecter
 * \brief Fenetre de connexion (première fenetre du programme)
 * C'est la fenetre de connexion au serveur. Elle demande a l'utilisateur
 * l'adresse et le port de la connexion.
 * @param parent
 */
class Connecter : public QDialog
{
    Q_OBJECT

public:
    explicit Connecter(QWidget *parent = 0);
    ~Connecter();

public slots:
    bool on_BoutonConnexion_clicked();
    void on_BoutonQuitter_clicked();

private:
    Ui::Connecter *ui;
    LClient *client;
    Configuration *config;
    Identification *identif;
};

#endif // CONNECTER_HPP
