#ifndef IDENTIFICATION_HPP
#define IDENTIFICATION_HPP

#include <QWidget>
#include <QtGui>
#include "LClient.h"
#include "mainwindow.hpp"

namespace Ui {
    class Identification;
}

/**
 * \class Identification
 * \brief Fenetre d'identification du joueur (login)
 * Cette fenetre va demander au joueur son login et va ensuite ouvrir la
 * fenetre principale de la partie une fois tous les joueurs connectés.
 * @param _client pointeur sur l'instance de LClient déclarée précédemment
 * @param parent
 */
class Identification : public QWidget
{
    Q_OBJECT

public:
    explicit Identification(LClient *_client,QWidget *parent = 0);
    ~Identification();
public slots:
    void on_BoutonValider_clicked();

private:
    Ui::Identification *ui;
    LClient *client;
    MainWindow *mainW;
};

#endif // IDENTIFICATION_HPP
