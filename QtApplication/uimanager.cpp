#include "uimanager.h"

UIManager::UIManager(QGraphicsView *view, QWidget *parent): QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget;
    layout->addWidget(stackedWidget);

    // Créer les pages
    menuPage = new MenuPage;
    gamePage = new GamePage(view);
    levelPage = new LevelPage;

    // Ajouter les pages au stacked widget
    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(levelPage);

    // Page de départ
    stackedWidget->setCurrentWidget(menuPage);

    // Connexions des boutons
    connect(menuPage, &MenuPage::menu_playClickedSig, this, [this]() {
        qDebug() << "connect ok";
        stackedWidget->setCurrentWidget(gamePage);
        emit startGame();
        qDebug() << "le jeu commence";
    });

    connect(menuPage, &MenuPage::menu_levelClickedSig, this, [this]() {
        stackedWidget->setCurrentWidget(levelPage);
    });

    connect(gamePage, &GamePage::over_quitClickedSig, this, [this]() {
        stackedWidget->setCurrentWidget(menuPage);
    });

    connect(gamePage, &GamePage::menu_quitClickedSig, this, [this]() {
        stackedWidget->setCurrentWidget(menuPage);
    });

    connect(levelPage, &LevelPage::level_quitClickedSig, this, [this]() {
        stackedWidget->setCurrentWidget(menuPage);
    });
}

GamePage* UIManager::getGamePage()
{
    return gamePage;
}

MenuPage* UIManager::getMenuPage()
{
    return menuPage;
}

LevelPage* UIManager::getLevelPage()
{
    return levelPage;
}

void UIManager::changeButtons()
{
    if(stackedWidget->currentWidget()==menuPage)
    {
        getMenuPage()->changeButtons();
    }
    if(stackedWidget->currentWidget()==gamePage)
    {
        getGamePage()->changeButtons();
    }
    if(stackedWidget->currentWidget()==levelPage)
    {
        getLevelPage()->changeButtons();
    }
}

void UIManager::setupNextSelect()
{
    if(stackedWidget->currentWidget()==menuPage)
    {
        getMenuPage()->setupNextSelect();
    }
    if(stackedWidget->currentWidget()==gamePage)
    {
        getGamePage()->setupNextSelect();
    }
    if(stackedWidget->currentWidget()==levelPage)
    {
        getLevelPage()->setupNextSelect();
    }
}
void UIManager::updateHighlight()
{
    if(stackedWidget->currentWidget()==menuPage)
    {
        getMenuPage()->updateHighlight();
    }
    if(stackedWidget->currentWidget()==gamePage)
    {
        getGamePage()->updateHighlight();
    }
    if(stackedWidget->currentWidget()==levelPage)
    {
        getLevelPage()->updateHighlight();
    }
}
void UIManager::activateSelectedButton()
{
    if(stackedWidget->currentWidget()==menuPage)
    {
        qDebug() << "selection ui menu";
        getMenuPage()->activateSelectedButton();
        return;
    }
    if(stackedWidget->currentWidget()==gamePage)
    {
        qDebug() << "selection ui game";
        getGamePage()->activateSelectedButton();
        return;
    }
    if(stackedWidget->currentWidget()==levelPage)
    {
        qDebug() << "selection ui level";
        getLevelPage()->activateSelectedButton();
        return;
    }
}

void UIManager::potIsTurning()
{
    potTurns=true;
    if (stackedWidget->currentWidget()==getGamePage() && getGamePage()->gameIsOn()==true)
    {
        qDebug() << "show popup";
        getGamePage()->showMenuPopup();
    }
    else
    {
        changeButtons();
    }
}

void UIManager::potStops()
{
    potTurns=false;
    updateHighlight();
}

void UIManager::shootPressed()
{
    shootPress=true;
    activateSelectedButton();
    setupNextSelect();
}

void UIManager::shootReleased()
{
    shootPress=false;
}

void UIManager::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "touche de ui pesee";
    emit keyPressSig(event);
}

void UIManager::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "touche de ui relache";
    emit keyReleaseSig(event);
}
