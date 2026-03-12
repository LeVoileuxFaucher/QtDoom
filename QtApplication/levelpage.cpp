/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: levelpage.cpp
Description: Code for the page where the levels are selected
Modifications:
*/
#include "levelpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

LevelPage::LevelPage(QWidget *parent)
    : QWidget(parent)
{
    //titre de la page
    m_label = new QLabel("Choisir un niveau:");
    QFont fontLabel;
    fontLabel.setPointSize(20);
    m_label->setFont(fontLabel);
    m_label->setAlignment(Qt::AlignCenter);

    //bouton quitter
    m_quitterButton = new QPushButton("Quitter");
    m_quitterButton->setFixedSize(80, 30);
    //layout du bouton quitter
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_quitterButton, 0, Qt::AlignLeft);
    topLayout->addStretch();

    //boutons pour les niveaux
    m_niveau1Button = new QPushButton("Niveau 1");
    m_niveau2Button = new QPushButton("Niveau 2");
    m_niveau3Button = new QPushButton("Niveau 3");
    //layout des boutons level
    QHBoxLayout *levelsLayout = new QHBoxLayout;
    levelsLayout->addStretch();
    levelsLayout->addWidget(m_niveau1Button);
    levelsLayout->addSpacing(20);
    levelsLayout->addWidget(m_niveau2Button);
    levelsLayout->addSpacing(20);
    levelsLayout->addWidget(m_niveau3Button);
    levelsLayout->addStretch();
    //style des boutons
    QFont fontButton;
    fontButton.setPointSize(20);
    m_niveau1Button->setFont(fontButton);
    m_niveau2Button->setFont(fontButton);
    m_niveau3Button->setFont(fontButton);
    m_niveau1Button->setFixedSize(150, 120);
    m_niveau2Button->setFixedSize(150, 120);
    m_niveau3Button->setFixedSize(150, 120);

    //layout de la page
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(100);
    mainLayout->addWidget(m_label);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(levelsLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    //ajout a la liste
    menuButtons.append(m_quitterButton);
    menuButtons.append(m_niveau1Button);
    menuButtons.append(m_niveau2Button);
    menuButtons.append(m_niveau3Button);

    connect(m_quitterButton, &QPushButton::clicked, this, &LevelPage::level_quitClicked);
    connect(m_niveau1Button, &QPushButton::clicked, this, &LevelPage::level_1Clicked);
    connect(m_niveau2Button, &QPushButton::clicked, this, &LevelPage::level_2Clicked);
    connect(m_niveau3Button, &QPushButton::clicked, this, &LevelPage::level_3Clicked);
    updateHighlight();
}

void LevelPage::updateHighlight()
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

void LevelPage::activateSelectedButton()
{
    qDebug() << "click selection dans menu";
    if (currentIndex == 0)
    {
        level_quitClicked();
    }
    else if (currentIndex == 1)
    {
        level_1Clicked();
    }
    else if (currentIndex == 2)
    {
        level_2Clicked();
    }
    else if (currentIndex == 3)
    {
        level_3Clicked();
    }
}

void LevelPage::level_quitClicked()
{
    qDebug() << "menu_levelClicked";
    emit level_quitClickedSig();
}

void LevelPage::level_1Clicked()
{
    qDebug() << "level_1Clicked";
    emit level_1ClickedSig();
}

void LevelPage::level_2Clicked()
{
    qDebug() << "level_2Clicked";
    emit level_2ClickedSig();
}

void LevelPage::level_3Clicked()
{
    qDebug() << "level_3Clicked";
    emit level_3ClickedSig();
}

void LevelPage::changeButtons()
{
    qDebug() << "changeButtons";
    currentIndex++;
    if (currentIndex > 3)
    {
        currentIndex = 0;
    }
    qDebug() << "current index:" << currentIndex;
}

void LevelPage::setupNextSelect()
{
    qDebug() << "setup Next";
    currentIndex=0;
}
