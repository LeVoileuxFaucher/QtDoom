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
    mainLayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);
    addGameWidget(view);
    addMenuPopupWidget();
    addGameoverWidget();
    menuButtons.append(menu_retryButton);
    menuButtons.append(menu_quitButton);
    menuButtons.append(menu_continueButton);
    overButtons.append(over_retryButton);
    overButtons.append(over_quitButton);
    connectButtons();
    //stackedWidget->setCurrentWidget(gameOverWidget);
}

void GamePage::addGameWidget(QGraphicsView *view)
{
    gameWidget = new QWidget(this);
    centralWidget = new QWidget(this);
    gameLayout = new QVBoxLayout(gameWidget);
    centralLayout = new QVBoxLayout(centralWidget);
    gameLayout->addWidget(centralWidget);
    addBarreEtat();
    addVieProgressBar();
    addBallesNum();
    addBallesProgressBar();
    //layout du jeu
    centralLayout->addWidget(view);
    gameLayout->addWidget(centralWidget);
    addLayoutBarreEtat();
    gameLayout->addWidget(barWidget);
    stackedWidget->addWidget(gameWidget);
}

void GamePage::addVieProgressBar()
{
    labelVie = new QLabel("vie:");
    m_barVie = new QProgressBar;
    m_barVie->setFixedHeight(30);
    m_barVie->setFixedWidth(200);
    m_barVie->setTextVisible(false);
    m_barVie->setStyleSheet("QProgressBar{background-color:lightgrey; border: 2px solid black; border-radius: 5px;} QProgressBar::chunk{background-color:green;}");
    m_barVie->setRange(0,15);
    m_barVie->setValue(15); //a modifier
}

void GamePage::addBallesProgressBar()
{
    //qDebug("on entre dans la fonction");
    labelBalles = new QLabel("balles:");
    m_barBalles = new QProgressBar;
    m_barBalles->setFixedHeight(30);
    m_barBalles->setFixedWidth(102);
    m_barBalles->setTextVisible(false);
    m_barBalles->setStyleSheet("QProgressBar{background:#222; color: white; border: 2px solid #333; border-radius: 4px;} QProgressBar::chunk{background-color:white; width: 8px; margin-right:2px;}");
    m_barBalles->setRange(0,10);
    m_barBalles->setValue(10); //a modifier
}

void GamePage::addBallesNum()
{
    labelAmo = new QLabel("balles:");
    m_writeAmo = new QLineEdit;
    m_writeAmo->setFixedWidth(40);
    m_writeAmo->setReadOnly(true);
    m_writeAmo->setText(QString::number(10)); //a modifier
}

void GamePage::addBarreEtat()
{
    barWidget = new QWidget;
    barWidget->setStyleSheet("background-color: gray;");
    barWidget->setFixedHeight(100);
}

void GamePage::addLayoutBarreEtat()
{
    barLayout = new QHBoxLayout(barWidget);
    barLayout->addStretch();
    barLayout->addWidget(labelVie);
    barLayout->addWidget(m_barVie);
    barLayout->addSpacing(100);
    /*barLayout->addWidget(labelAmo);
    barLayout->addWidget(m_writeAmo);*/
    barLayout->addWidget(labelBalles);
    barLayout->addWidget(m_barBalles);
    barLayout->addStretch();
}

void GamePage::addMenuPopupWidget()
{
    addTitleMenu();
    addTitleMenuLayout();
    buttonLayout = new QVBoxLayout;
    //créer les boutons
    addRetryButtonMenu();
    addQuitButtonMenu();
    addContinueButtonMenu();
    //ajouter layout
    addRetryButtonMenuLayout();
    addQuitButtonMenuLayout();
    addContinueButtonMenuLayout();
    addPageMenuLayout();
    stackedWidget->addWidget(popupWidget);
}

void GamePage::addTitleMenu()
{
    popupWidget = new QWidget(this);  // Popup à afficher
    popupLayout = new QVBoxLayout(popupWidget);
    popupTitle = new QLabel("En pause");
    font.setPointSize(20);
    font.setBold(true);
    popupTitle->setFont(font);
    popupTitle->setAlignment(Qt::AlignCenter);
}

void GamePage::addTitleMenuLayout()
{
    popupLayout->addStretch();  // Espace avant le titre
    popupLayout->addWidget(popupTitle);
    popupLayout->addSpacing(20);
}

void GamePage::addRetryButtonMenu()
{
    menu_retryButton = new QPushButton("Recommencer");
    menu_retryButton->setStyleSheet("background-color: black; color: white;");
    menu_retryButton->setFixedSize(120, 40);
}

void GamePage::addContinueButtonMenu()
{
    menu_continueButton = new QPushButton("Continuer");
    menu_continueButton->setStyleSheet("background-color: black; color: white;");
    menu_continueButton->setFixedSize(120, 40);
}

void GamePage::addQuitButtonMenu()
{
    menu_quitButton = new QPushButton("Quitter");
    menu_quitButton->setStyleSheet("background-color: black; color: white;");
    menu_quitButton->setFixedSize(120, 40);
}

void GamePage::addRetryButtonMenuLayout()
{
    retryButtonLayout = new QHBoxLayout();
    retryButtonLayout->addStretch();
    retryButtonLayout->addWidget(menu_retryButton);
    retryButtonLayout->addStretch();
}

void GamePage::addContinueButtonMenuLayout()
{
    continueButtonLayout = new QHBoxLayout();
    continueButtonLayout->addStretch();
    continueButtonLayout->addWidget(menu_continueButton);
    continueButtonLayout->addStretch();
}

void GamePage::addQuitButtonMenuLayout()
{
    quitButtonLayout = new QHBoxLayout();
    quitButtonLayout->addStretch();
    quitButtonLayout->addWidget(menu_quitButton);
    quitButtonLayout->addStretch();
}

void GamePage::addPageMenuLayout()
{
    buttonLayout->addLayout(retryButtonLayout);
    buttonLayout->addLayout(quitButtonLayout);
    buttonLayout->addLayout(continueButtonLayout);
    popupLayout->addLayout(buttonLayout);
    popupLayout->addStretch();
}

void GamePage::addGameoverWidget()
{
    gameOverWidget = new QWidget(this);
    gameOverLayout = new QVBoxLayout(gameOverWidget);
    addTitleOver();
    addRetryButtonOver();
    addQuitButtonOver();
    //ajouter layout
    addTitleOverLayout();
    addRetryButtonOverLayout();
    addQuitButtonOverLayout();
    addPageOverLayout();
    stackedWidget->addWidget(gameOverWidget);
    mainLayout->addWidget(stackedWidget);
}

void GamePage::addTitleOver()
{
    gameOverTitle = new QLabel("Game Over");
    overFont.setPointSize(20);
    overFont.setBold(true);
    gameOverTitle->setFont(font);
    gameOverTitle->setAlignment(Qt::AlignCenter);  // Centrer le titre
}

void GamePage::addRetryButtonOver()
{
    over_retryButton = new QPushButton("Recommencer");
    over_retryButton->setStyleSheet("background-color: black; color: white;");
    over_retryButton->setFixedSize(120, 40);
}

void GamePage::addQuitButtonOver()
{
    over_quitButton = new QPushButton("Quitter");
    over_quitButton->setStyleSheet("background-color: black; color: white;");
    over_quitButton->setFixedSize(120, 40);
}

void GamePage::addTitleOverLayout()
{
    gameOverLayout->addStretch();  // Espace avant le titre
    gameOverLayout->addWidget(gameOverTitle);
    gameOverLayout->addSpacing(20);
    buttonOverLayout = new QVBoxLayout;
}

void GamePage::addRetryButtonOverLayout()
{
    retryOverButtonLayout = new QHBoxLayout();
    retryOverButtonLayout->addStretch();
    retryOverButtonLayout->addWidget(over_retryButton);
    retryOverButtonLayout->addStretch();
}

void GamePage::addQuitButtonOverLayout()
{
    quitOverButtonLayout = new QHBoxLayout();
    quitOverButtonLayout->addStretch();
    quitOverButtonLayout->addWidget(over_quitButton);
    quitOverButtonLayout->addStretch();
}

void GamePage::addPageOverLayout()
{
    buttonOverLayout->addLayout(retryOverButtonLayout);
    buttonOverLayout->addLayout(quitOverButtonLayout);
    gameOverLayout->addLayout(buttonOverLayout);
    gameOverLayout->addStretch();
}

void GamePage::connectButtons()
{
    //connect les boutons
    connect(menu_quitButton, &QPushButton::clicked, this, &GamePage::menu_quitClicked);
    connect(menu_retryButton, &QPushButton::clicked, this, &GamePage::menu_retryClicked);
    connect(over_quitButton, &QPushButton::clicked, this, &GamePage::over_quitClicked);
    connect(over_retryButton, &QPushButton::clicked, this, &GamePage::over_retryClicked);
    connect(menu_continueButton, &QPushButton::clicked, this, &GamePage::menu_continueClicked);
    if (stackedWidget->currentWidget()==gameOverWidget)
    {
        //qDebug() << "active==gameOver";
    }
    if (stackedWidget->currentWidget()==popupWidget)
    {
        //qDebug() << "active==popup";
    }
}

void GamePage::showEvent(QShowEvent *event)
{
}

void GamePage::updateHighlight()
{
    //qDebug() << "update light";
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
    //qDebug() << "click selection dans game";
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
    //qDebug() << "menu_quitClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_quitClickedSig();
}

void GamePage::menu_retryClicked()
{
    //qDebug() << "menu_retryClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_retryClickedSig();
}

void GamePage::menu_continueClicked()
{
    //qDebug() << "menu_continueClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit menu_continueClickedSig();
}

void GamePage::over_quitClicked()
{
    //qDebug() << "over_quitClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit over_quitClickedSig();
}

void GamePage::over_retryClicked()
{
    //qDebug() << "over_retryClicked";
    stackedWidget->setCurrentWidget(gameWidget);
    emit over_retryClickedSig();
}

void GamePage::changeButtons()
{
    //qDebug() << "changeButtons";
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
    //qDebug() << "menu current index:" << menuCurrentIndex;
    //qDebug() << "over current index:" << overCurrentIndex;
}

void GamePage::setupNextSelect()
{
    //qDebug() << "setup Next";
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

QLineEdit* GamePage::amoEdit()
{
    return m_writeAmo;
}

void GamePage::updateVie(int vie)
{
    m_barVie->setValue(vie);
}

void GamePage::updateBalles(int balles)
{
    m_barBalles->setValue(balles);
}

void GamePage::gameOver()
{
    stackedWidget->setCurrentWidget(gameOverWidget);
    updateHighlight();
}
