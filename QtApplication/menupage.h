/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: menupage.h
Description: Code for the menu page of the game
Modifications:
*/
#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include <QPushButton>

class MenuPage : public QWidget
{
    Q_OBJECT
public:
    MenuPage(QWidget *parent = nullptr);

    QPushButton* playButton() const { return menu_playButton; }
    QPushButton* levelButton() const { return menu_levelButton; }
    void menu_levelClicked();
    void menu_playClicked();

private:
    QPushButton *menu_playButton;
    QPushButton *menu_levelButton;
    QVector<QPushButton*> menuButtons;
    int currentIndex=0;

public slots:
    void changeButtons();
    void setupNextSelect();
    void updateHighlight();
    void activateSelectedButton();

signals:
    void menu_levelClickedSig();
    void menu_playClickedSig();
};

#endif // MENUPAGE_H
