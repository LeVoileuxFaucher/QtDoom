/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: menupage.cpp
Description: Code for the menu page of the game
Modifications:
*/
#include "menupage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label_doom = new QLabel("DOOM");
    QFont font;
    font.setPointSize(36);
    font.setBold(true);
    label_doom->setFont(font);

    menu_playButton = new QPushButton("Play");
    menu_playButton->setMinimumSize(150, 40);
    menu_playButton->setStyleSheet("QPushButton{border-width: 4px; border-style: solid; border-color: green; border-radius: 15px; color:black;} QPushButton:hover{background-color:blue");


    menu_levelButton = new QPushButton("Niveaux");
    menu_levelButton->setMinimumSize(80, 25);
    menu_levelButton->setStyleSheet("border-width: 1px; border-style: solid; border-color: black; color:black;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(label_doom, 0, Qt::AlignCenter);
    layout->addSpacing(30);
    layout->addWidget(menu_levelButton, 0, Qt::AlignCenter);
    layout->addSpacing(30);
    layout->addWidget(menu_playButton, 0, Qt::AlignCenter);
    layout->addStretch();

    //ajout a la liste
    menuButtons.append(menu_levelButton);
    menuButtons.append(menu_playButton);

    connect(menu_levelButton, &QPushButton::clicked, this, &MenuPage::menu_levelClicked);
    connect(menu_playButton, &QPushButton::clicked, this, &MenuPage::menu_playClicked);
    updateHighlight();
}


void MenuPage::updateHighlight()
{
    qDebug() << "update light";
    // Réinitialiser les styles de tous les boutons
    for (int i=0; i<menuButtons.size(); i++) {
        menuButtons[i]->setStyleSheet("background-color: black; color: white;");
    }

    // Appliquer un style au bouton sélectionné
    if (currentIndex < menuButtons.size())
    {
        menuButtons[currentIndex]->setStyleSheet("background-color: darkgray; color: black;");
    }
}

void MenuPage::activateSelectedButton()
{
    qDebug() << "click selection dans menu";
    if (currentIndex == 0)
    {
        menu_levelClicked();
    }
    else if (currentIndex == 1)
    {
        menu_playClicked();
    }
}

void MenuPage::menu_levelClicked()
{
    qDebug() << "menu_levelClicked";
    emit menu_levelClickedSig();
}

void MenuPage::menu_playClicked()
{
    qDebug() << "menu_playClicked";
    emit menu_playClickedSig();
}

void MenuPage::changeButtons()
{
    qDebug() << "changeButtons";
    currentIndex++;
    if (currentIndex > 1)
    {
        currentIndex = 0;
    }
    qDebug() << "current index:" << currentIndex;
}

void MenuPage::setupNextSelect()
{
    qDebug() << "setup Next";
    currentIndex=0;
    updateHighlight();
}
