#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtGui>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#include "LClient.h"

namespace Ui {
    class MainWindow;
}

/**
 * \brief fenetre principale de jeu
 * @param _client pointeur sur le client précédemment déclaré.
 * @param parent
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(LClient *_client,QWidget *parent = 0);
    ~MainWindow();
    void verrouillerBoutons();
    void deverrouillerBoutons();
    void montrerDes();
    void cacherDes();
    void montrerPari();
    void cacherPari();
    void toutCacher();
    void toutAfficher();
    void actualiserDes();
    LClient *getClient();
    int* getInterpretation();
    Ui::MainWindow *getUi();
    void actualiserPari();

public slots:
    void on_BoutonParier_clicked();
    void on_BoutonQuitter_clicked();
    void on_BoutonDeconnexion_clicked();
    void on_BoutonDudo_clicked();
    void jouer();

private:
    Ui::MainWindow *ui;
    LClient *client;
    QTimer *timer;
    int interpretation;
    pthread_t threadInter;
    pthread_t threadJeu;
    int *lancer;
    int nbDes;

};

void *th_interpreter(void *p_data);
void *th_recevoir(void *p_data);

#endif // MAINWINDOW_HPP
