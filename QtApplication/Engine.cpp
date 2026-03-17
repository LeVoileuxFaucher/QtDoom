/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Engine.cpp
Description: Code file for the game engine handling all events.
Modifications:
*/

#include"engine.h"

Engine::Engine(QGraphicsScene *scene, int width, int height, QObject *parent, QGraphicsView *view)
    : QObject(parent)
{
    uiManager = new UIManager(view);

    cManager = new ControllerManager();
    gManager = new GameManager();
    rManager = new RenderManager(scene, width, height);

    m_width = width;
    m_height = height;

    m_scene = scene;
    m_view = view;

    gManager->loadMap("WadLvl1.txt");

    connect(uiManager, SIGNAL(startGame()), this, SLOT(start()));
    connect(uiManager, SIGNAL(keyPressSig(QKeyEvent*)), cManager, SLOT(keyPressedEvent(QKeyEvent*)));
    connect(uiManager, SIGNAL(keyReleaseSig(QKeyEvent*)), cManager, SLOT(keyReleasedEvent(QKeyEvent*)));
    //dans ui
    connect(cManager, SIGNAL(potTurnedSig()), uiManager, SLOT(potIsTurning()));
    connect(cManager, SIGNAL(potStopedSig()), uiManager, SLOT(potStops()));
    connect(cManager, SIGNAL(shootPressedSig()), uiManager, SLOT(shootPressed()));
    connect(cManager, SIGNAL(shootReleasedSig()), uiManager, SLOT(shootReleased()));
    //pause, continue, recommence jeu
    connect(uiManager, SIGNAL(pauseGame()), this, SLOT(pauseGame()));
    connect(uiManager->getGamePage(), SIGNAL(menu_continueClickedSig()), this, SLOT(resumeGame()));
    connect(uiManager->getGamePage(), SIGNAL(menu_quitClickedSig()), this, SLOT(quitGame()));
    connect(uiManager->getGamePage(), SIGNAL(menu_retryClickedSig()), this, SLOT(restartGame()));
    //playerDead gameOver
    connect(gManager, SIGNAL(playerDead()), this, SLOT(gameOver()));
    connect(uiManager->getGamePage(), SIGNAL(over_quitClickedSig()), this, SLOT(quitGame()));
    connect(uiManager->getGamePage(), SIGNAL(over_retryClickedSig()), this, SLOT(restartGame()));
    // This was missing — without it gameLoop() never gets called
    connect(&timer, &QTimer::timeout, this, &Engine::gameLoop);
    connect(gManager->getWeapon(), SIGNAL(sigUpdateBalles(int)), uiManager, SLOT(updateBalles(int)));
    connect(gManager, SIGNAL(sigUpdateVie(int)), uiManager, SLOT(updateVie(int)));
}

Engine::~Engine()
{
}

void Engine::start()
{
    elapsedTimer.start();
    timer.start(1000 / TARGET_FPS);
}

void Engine::pauseGame()
{
    qDebug("pauseGame");
    timer.stop();
}

void Engine::resumeGame()
{
    qDebug("resumeGame");
    timer.start(1000 / TARGET_FPS);
}

void Engine::restartGame()
{
    qDebug("restartGame");
    elapsedTimer.restart();
    gManager->restartGame();
    resumeGame();
}

void Engine::quitGame()
{
    qDebug("quitGame");
    elapsedTimer.restart();
    gManager->restartGame();
}

void Engine::gameOver()
{
    pauseGame();
    uiManager->getGamePage()->gameOver();
}

void Engine::gameLoop()
{
    int currentWidth = m_view->width();
    int currentHeight = m_view->height();
    Weapon* weapon = gManager->getPlayer()->getWeapon();

    if(currentWidth!=m_width || currentHeight!=m_height)
    {
        m_width=currentWidth;
        m_height=currentHeight;
        m_scene->setSceneRect(0, 0, currentWidth, currentHeight);
        rManager->updateScreenSize(currentWidth, currentHeight);
    }

    float deltaTime = elapsedTimer.restart() / 1000.0f;
    if (deltaTime > 0.1f) deltaTime = 0.1f;

    if(cManager->movingBack()) gManager->getPlayer()->setPosition(gManager->getPlayer()->getPosition().x+(0.5f*cos(gManager->getPlayer()->getAngle() - M_PI/2)), gManager->getPlayer()->getPosition().y+(0.5f*sin(gManager->getPlayer()->getAngle() - M_PI/2)));
    if(cManager->movingLeft()) gManager->getPlayer()->setPosition(gManager->getPlayer()->getPosition().x-(0.5f*cos(gManager->getPlayer()->getAngle())), gManager->getPlayer()->getPosition().y-(0.5f*sin(gManager->getPlayer()->getAngle())));
    if(cManager->movingRight()) gManager->getPlayer()->setPosition(gManager->getPlayer()->getPosition().x+(0.5f*cos(gManager->getPlayer()->getAngle())), gManager->getPlayer()->getPosition().y+(0.5f*sin(gManager->getPlayer()->getAngle())));
    if(cManager->movingFront()) gManager->getPlayer()->setPosition(gManager->getPlayer()->getPosition().x+(0.5f*cos(gManager->getPlayer()->getAngle() + M_PI/2)), gManager->getPlayer()->getPosition().y+(0.5f*sin(gManager->getPlayer()->getAngle() + M_PI/2)));
    if(cManager->rotatingLeft()) gManager->getPlayer()->setAngle(gManager->getPlayer()->getAngle()+0.05f);
    if(cManager->rotatingRight()) gManager->getPlayer()->setAngle(gManager->getPlayer()->getAngle()-0.05f);
    if (cManager->justShot())
    {

        rManager->setHit(false);
        if (weapon && weapon->canShoot())
        {
            QGraphicsView* m_view = rManager->getView();
            QPoint globalMousePos = QCursor::pos();
            QPoint viewMousePos   = m_view->mapFromGlobal(globalMousePos);

            bool hit = gManager->shoot(viewMousePos, m_view->size());
            rManager->setHit(hit);
            float endX   = viewMousePos.x();
            float endY   = viewMousePos.y();

            rManager->renderRay(endX, endY, 5);
        }
        cManager->resetShot();

    }

    if(cManager->isReloading())
    {

        if(weapon!=nullptr)
        {
            weapon->reload();
        }
        cManager->resetReload();
    }
    rManager->render(*gManager->getPlayer(),*gManager->getEnemy(), gManager->getBSP(), gManager->getVerteces());

    if(cManager->isPowerUp())
    {
        if(weapon!=nullptr)
         {
             weapon->powerUp();
           qDebug() << weapon->getCurrentAmmo() << weapon->getFireRate();
         }
        cManager->resetPowerUp();
    }
    gManager->update(deltaTime, rManager->getRenderedWalls());
    gManager->getPlayer()->getWeapon()->updatePowerUp();
    rManager->setPowerUpActive(weapon->isPoweredUp());
}

ControllerManager* Engine::getcManager() const
{
    return cManager;
}

UIManager* Engine::getuiManager() const
{
    return uiManager;
}
