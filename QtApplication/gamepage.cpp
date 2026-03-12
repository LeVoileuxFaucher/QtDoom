/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: gamepage.cpp
Description: Code for the page where the game is played
Modifications:
*/

#include "gamepage.h"

GamePage::GamePage(QGraphicsView *view, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    stackedWidget = new QStackedWidget(this);

    //------game Widget------
    gameWidget = new QWidget(this);  // Création du centralWidget
    QVBoxLayout *gameLayout = new QVBoxLayout(gameWidget);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    gameLayout->addWidget(centralWidget);
    //----barre d'état au bas de l'écran----
    QWidget *barWidget = new QWidget;
    barWidget->setStyleSheet("background-color: gray;");
    barWidget->setFixedHeight(100);
    QHBoxLayout *barLayout = new QHBoxLayout(barWidget);
    //barre de vie du joueur
    QLabel *labelVie = new QLabel("vie:");
    m_barVie = new QProgressBar;
    m_barVie->setFixedHeight(30);
    m_barVie->setFixedWidth(200);
    m_barVie->setTextVisible(false);
    m_barVie->setStyleSheet("QProgressBar{background-color:lightgrey; border: 2px solid black; border-radius: 5px;} QProgressBar::chunk{background:green;}");
    m_barVie->setValue(80); //a modifier
    //nb de balles tirées
    QLabel *labelAmo = new QLabel("balles:");
    m_writeAmo = new QLineEdit;
    m_writeAmo->setFixedWidth(40);
    m_writeAmo->setReadOnly(true);
    m_writeAmo->setText(QString::number(10)); //a modifier
    // Ajouter le jeu (view) à l'application, il occupe toute la fenêtre
    centralLayout->addWidget(view);
    gameLayout->addWidget(centralWidget);
    //layout de la barre d'état
    barLayout->addStretch();
    barLayout->addWidget(labelVie);
    barLayout->addWidget(m_barVie);
    barLayout->addSpacing(100);
    barLayout->addWidget(labelAmo);
    barLayout->addWidget(m_writeAmo);
    barLayout->addStretch();
    gameLayout->addWidget(barWidget);
    // Layout de la fenêtre principale (jeu)
    stackedWidget->addWidget(gameWidget);

    //----popup Widget menu----
    popupWidget = new QWidget(this);  // Popup à afficher
    QVBoxLayout *popupLayout = new QVBoxLayout(popupWidget);
    QLabel *popupTitle = new QLabel("En pause");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    popupTitle->setFont(font);
    popupTitle->setAlignment(Qt::AlignCenter);  // Centrer le titre
    // Ajouter le titre au layout avec un espace autour
    popupLayout->addStretch();  // Espace avant le titre
    popupLayout->addWidget(popupTitle);
    popupLayout->addSpacing(20);
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    // Création des 3 boutons
    menu_retryButton = new QPushButton("Recommencer");
    menu_retryButton->setStyleSheet("background-color: black; color: white;");
    menu_retryButton->setFixedSize(120, 40);
    menu_quitButton = new QPushButton("Quitter");
    menu_quitButton->setStyleSheet("background-color: black; color: white;");
    menu_quitButton->setFixedSize(120, 40);
    menu_continueButton = new QPushButton("Continuer");
    menu_continueButton->setStyleSheet("background-color: black; color: white;");
    menu_continueButton->setFixedSize(120, 40);
    //Centrer chaque bouton horizontalement
    QHBoxLayout *retryButtonLayout = new QHBoxLayout();
    retryButtonLayout->addStretch();
    retryButtonLayout->addWidget(menu_retryButton);
    retryButtonLayout->addStretch();
    QHBoxLayout *quitButtonLayout = new QHBoxLayout();
    quitButtonLayout->addStretch();
    quitButtonLayout->addWidget(menu_quitButton);
    quitButtonLayout->addStretch();
    QHBoxLayout *continueButtonLayout = new QHBoxLayout();
    continueButtonLayout->addStretch();
    continueButtonLayout->addWidget(menu_continueButton);
    continueButtonLayout->addStretch();
    // Ajouter les boutons centrés au layout vertical
    buttonLayout->addLayout(retryButtonLayout);
    buttonLayout->addLayout(quitButtonLayout);
    buttonLayout->addLayout(continueButtonLayout);
    popupLayout->addLayout(buttonLayout);
    popupLayout->addStretch();
    // Ajouter popupWidget au stackedWidget
    stackedWidget->addWidget(popupWidget);

    //----popup Widget gameover----
    gameOverWidget = new QWidget(this);  // Popup à afficher
    QVBoxLayout *gameOverLayout = new QVBoxLayout(gameOverWidget);
    QLabel *gameOverTitle = new QLabel("Game Over");
    QFont overFont;
    overFont.setPointSize(20);
    overFont.setBold(true);
    gameOverTitle->setFont(font);
    gameOverTitle->setAlignment(Qt::AlignCenter);  // Centrer le titre
    // Ajouter le titre au layout avec un espace autour
    gameOverLayout->addStretch();  // Espace avant le titre
    gameOverLayout->addWidget(gameOverTitle);
    gameOverLayout->addSpacing(20);
    QVBoxLayout *buttonOverLayout = new QVBoxLayout;
    // Création des 3 boutons
    over_retryButton = new QPushButton("Recommencer");
    over_retryButton->setStyleSheet("background-color: black; color: white;");
    over_retryButton->setFixedSize(120, 40);
    over_quitButton = new QPushButton("Quitter");
    over_quitButton->setStyleSheet("background-color: black; color: white;");
    over_quitButton->setFixedSize(120, 40);
    //Centrer chaque bouton horizontalement
    QHBoxLayout *retryOverButtonLayout = new QHBoxLayout();
    retryOverButtonLayout->addStretch();
    retryOverButtonLayout->addWidget(over_retryButton);
    retryOverButtonLayout->addStretch();
    QHBoxLayout *quitOverButtonLayout = new QHBoxLayout();
    quitOverButtonLayout->addStretch();
    quitOverButtonLayout->addWidget(over_quitButton);
    quitOverButtonLayout->addStretch();
    // Ajouter les boutons centrés au layout vertical
    buttonOverLayout->addLayout(retryOverButtonLayout);
    buttonOverLayout->addLayout(quitOverButtonLayout);
    gameOverLayout->addLayout(buttonOverLayout);
    gameOverLayout->addStretch();
    // Ajouter popupWidget au stackedWidget
    stackedWidget->addWidget(gameOverWidget);
    mainLayout->addWidget(stackedWidget);

    //ajout aux listes
    menuButtons.append(menu_retryButton);
    menuButtons.append(menu_quitButton);
    menuButtons.append(menu_continueButton);
    overButtons.append(over_retryButton);
    overButtons.append(over_quitButton);
    //connect les boutons
    connect(menu_quitButton, &QPushButton::clicked, this, &GamePage::menu_quitClicked);
    connect(menu_retryButton, &QPushButton::clicked, this, &GamePage::menu_retryClicked);
    connect(over_quitButton, &QPushButton::clicked, this, &GamePage::over_quitClicked);
    connect(over_retryButton, &QPushButton::clicked, this, &GamePage::over_retryClicked);
    connect(menu_continueButton, &QPushButton::clicked, this, &GamePage::menu_continueClicked);
    if (stackedWidget->currentWidget()==gameOverWidget)
    {
        qDebug() << "active==gameOver";
    }
    if (stackedWidget->currentWidget()==popupWidget)
    {
        qDebug() << "active==popup";
    }
}

void GamePage::showEvent(QShowEvent *event)
{
}

void GamePage::updateHighlight()
{
    qDebug() << "update light";
    // Réinitialiser les styles de tous les boutons
    for (int i=0; i<menuButtons.size(); i++) {
        menuButtons[i]->setStyleSheet("background-color: black; color: white;");
    }
    for (int i=0; i<overButtons.size(); i++) {
        overButtons[i]->setStyleSheet("background-color: black; color: white;");
    }

    // Appliquer un style au bouton sélectionné
    if (stackedWidget->currentWidget()==popupWidget)
    {
        if (menuCurrentIndex < menuButtons.size())
        {
            menuButtons[menuCurrentIndex]->setStyleSheet("background-color: darkgray; color: black;");
        }
    }
    if (stackedWidget->currentWidget()==gameOverWidget)
    {
        if (overCurrentIndex < overButtons.size())
        {
            overButtons[overCurrentIndex]->setStyleSheet("background-color: darkgray; color: black;");
        }
    }
}

void GamePage::activateSelectedButton()
{
    qDebug() << "click selection dans game";
    if (stackedWidget->currentWidget() == popupWidget) {
        if (menuCurrentIndex == 0) {
            menu_retryClicked();
        } else if (menuCurrentIndex == 1) {
            menu_quitClicked();
        } else if (menuCurrentIndex == 2) {
            menu_continueClicked();
        }
    }
    else if (stackedWidget->currentWidget() == gameOverWidget) {
        if (overCurrentIndex == 0) {
            over_retryClicked();
        } else if (overCurrentIndex == 1) {
            over_quitClicked();
        }
    }
}

void GamePage::menu_quitClicked()
{
    qDebug() << "menu_quitClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_quitClickedSig();
}

void GamePage::menu_retryClicked()
{
    qDebug() << "menu_retryClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_retryClickedSig();
}

void GamePage::menu_continueClicked()
{
    qDebug() << "menu_continueClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_continueClickedSig();
}

void GamePage::over_quitClicked()
{
    qDebug() << "over_quitClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit over_quitClickedSig();
}

void GamePage::over_retryClicked()
{
    qDebug() << "over_retryClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit over_retryClickedSig();
}

void GamePage::changeButtons()
{
    qDebug() << "changeButtons";
    if (stackedWidget->currentWidget() == popupWidget) {
        menuCurrentIndex++;
        if (menuCurrentIndex > 2) {
            menuCurrentIndex = 0;
        }
    }
    else if (stackedWidget->currentWidget() == gameOverWidget) {
        overCurrentIndex++;
        if (overCurrentIndex > 1) {
            overCurrentIndex = 0;
        }
    }
    qDebug() << "menu current index:" << menuCurrentIndex;
    qDebug() << "over current index:" << overCurrentIndex;
}

void GamePage::setupNextSelect()
{
    qDebug() << "setup Next";
    menuCurrentIndex=0;
    overCurrentIndex = 0;
}

void GamePage::showMenuPopup()
{
    stackedWidget->setCurrentWidget(popupWidget);
    updateHighlight();
}

bool GamePage::gameIsOn()
{
    return stackedWidget->currentWidget()==gameWidget;
}
