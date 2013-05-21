#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QWidget>

#include <QtGui>
#include "LClient.h"
#include "identification.hpp"
#include "mainwindow.hpp"


namespace Ui {
    class Configuration;
}

/**
 * \brief classe configuration
 * Constructeur de la classe Configuration, qui ouvre une fenêtre de
 * configuration pour que l'utilisateur puisse parametrer le serveur.
 * Cette classe prend en paramètre un pointeur sur une instance de LClient,
 * pour ne pas perdre le client de vue.
 *
 * @param _client pointeur sur l'instance de client précédement déclarée.
 * @param parent
 */
class Configuration : public QWidget
{
    Q_OBJECT

public:
    explicit Configuration(LClient *_client, QWidget *parent = 0);
    ~Configuration();

public slots:
    void on_BoutonValider_clicked();

private:
    Ui::Configuration *ui;
    LClient *client;
    MainWindow *mainW;
};

#endif // CONFIGURATION_HPP
