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
    connect(uiManager->getGamePage(), SIGNAL(keyPressSig(QKeyEvent*)), cManager, SLOT(keyPressedEvent(QKeyEvent*)));
    connect(uiManager->getGamePage(), SIGNAL(keyReleaseSig(QKeyEvent*)), cManager, SLOT(keyReleasedEvent(QKeyEvent*)));
    // This was missing — without it gameLoop() never gets called
    connect(&timer, &QTimer::timeout, this, &Engine::gameLoop);
}

Engine::~Engine()
{
}

void Engine::start()
{
    elapsedTimer.start();
    timer.start(1000 / TARGET_FPS);
}

void Engine::gameLoop()
{
    int currentWidth = m_view->width();
    int currentHeight = m_view->height();

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
        Weapon* weapon = gManager->getPlayer()->getWeapon();

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
        Weapon* weapon = gManager->getPlayer()->getWeapon();

        if(weapon!=nullptr)
        {
            weapon->reload();
        }
        cManager->resetReload();
    }

    if(cManager->isPowerUp())
    {
         Weapon* weapon = gManager->getPlayer()->getWeapon();
        if(weapon!=nullptr)
         {
             weapon->powerUp();
         }
        cManager->resetPowerUp();
    }
    rManager->render(*gManager->getPlayer(),*gManager->getEnemy(), gManager->getBSP());
    gManager->update(deltaTime, rManager->getRenderedWalls());

}

ControllerManager* Engine::getcManager() const
{
    return cManager;
}

UIManager* Engine::getuiManager() const
{
    return uiManager;
}
