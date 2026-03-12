/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: gamepage.h
Description: Code for the page where the game is played
Modifications:
*/

#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QStackedWidget>

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QGraphicsView *view, QWidget *parent = nullptr);
    bool gameIsOn();

private:
    QStackedWidget *stackedWidget;
    QWidget *gameWidget;
    QWidget *popupWidget;
    QWidget *gameOverWidget;

    // Les boutons pour le popup menu
    QPushButton *menu_retryButton;
    QPushButton *menu_quitButton;
    QPushButton *menu_continueButton;

    // Les boutons pour le popup gameOver
    QPushButton *over_retryButton;
    QPushButton *over_quitButton;

    //selection boutons
    int menuCurrentIndex=0;
    int overCurrentIndex=0;

    // La barre de vie et le nombre de balles
    QProgressBar *m_barVie;
    QLineEdit *m_writeAmo;
    QPushButton *m_shootButton;

    //listes des boutons
    QVector<QPushButton*> menuButtons;
    QVector<QPushButton*> overButtons;

    bool potTurns=false;
    bool shootPress=false;

signals:
    void menu_quitClickedSig();
    void menu_retryClickedSig();
    void menu_continueClickedSig();
    void over_quitClickedSig();
    void over_retryClickedSig();

protected:
    void showEvent(QShowEvent *event) override;
    void menu_quitClicked();
    void menu_retryClicked();
    void menu_continueClicked();
    void over_quitClicked();
    void over_retryClicked();

public slots:
    void changeButtons();
    void setupNextSelect();
    void updateHighlight();
    void activateSelectedButton();
    void showMenuPopup();
};

#endif // GAMEPAGE_H
