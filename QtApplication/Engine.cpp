/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Engine.cpp
Description: Code file for the game engine handling all events.
Modifications:
*/

#include"engine.h"
#include <cmath>

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

    QString mapPath = QCoreApplication::applicationDirPath() + "/../../WadLvl1.txt";
    gManager->loadMap(mapPath.toStdString());

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
    connect(cManager, SIGNAL(confirmSig()), uiManager, SLOT(shootPressed()));
    connect(&timer, &QTimer::timeout, this, &Engine::gameLoop);
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
    // ---------------------------------------------------------------
    // Détection de bordure : toujours active (mode curseur ON ou OFF).
    // Mode curseur ON  -> on utilise m_smoothX (position Arduino lissée).
    // Mode curseur OFF -> on utilise QCursor::pos() (souris physique).
    // ---------------------------------------------------------------
    {
        QPoint viewTopLeft = m_view->mapToGlobal(QPoint(0, 0));
        float  viewLeft    = (float)viewTopLeft.x();
        float  viewRight   = viewLeft + (float)m_view->width();

        float cursorX;
        if (cManager->isCursorModeEnabled() && m_smoothX >= 0.0f)
            cursorX = m_smoothX;
        else
            cursorX = (float)QCursor::pos().x();

        cManager->setBorderRotLeft ( (cursorX - viewLeft)  < BORDER_ZONE );
        cManager->setBorderRotRight( (viewRight - cursorX) < BORDER_ZONE );
    }
    // ---------------------------------------------------------------

    // Rotation clavier (Q/E) OU rotation par bordure
    // Rotation nette pour éviter que Q+E simultanés s'annulent et bloquent
    {
        int rotDir = 0;
        if (cManager->rotatingLeft()  || cManager->rotatingLeftBorder())  rotDir += 1;
        if (cManager->rotatingRight() || cManager->rotatingRightBorder()) rotDir -= 1;
        if (rotDir != 0)
            gManager->getPlayer()->setAngle(gManager->getPlayer()->getAngle() + rotDir * BORDER_ROT_SPEED * deltaTime);
    }

    // ---------------------------------------------------------------
    // Mode curseur Arduino (lissage analogique par lerp)
    // ---------------------------------------------------------------
    if (cManager->isCursorModeEnabled())
    {
        if (cManager->hasCursorUpdate())
        {
            int rawX = cManager->getCursorRawX();
            int rawY = cManager->getCursorRawY();

            // rawX/rawY = tilt encodé en 0-255 (128 = centre)
            // On mappe directement sur la taille de la vue Qt
            {
                QPoint viewTopLeft = m_view->mapToGlobal(QPoint(0, 0));
                int viewW = m_view->width();
                int viewH = m_view->height();

                // Normalise 0-255 → 0.0-1.0, centre à 0.5
                float normX = (float)rawX / 255.0f;
                float normY = (float)rawY / 255.0f;

                float targetX = viewTopLeft.x() + normX * viewW;
                float targetY = viewTopLeft.y() + normY * viewH;

                targetX = qBound((float)viewTopLeft.x(), targetX, (float)(viewTopLeft.x() + viewW - 1));
                targetY = qBound((float)viewTopLeft.y(), targetY, (float)(viewTopLeft.y() + viewH - 1));

                if (m_smoothX < 0.0f) { m_smoothX = targetX; m_smoothY = targetY; }

                float alpha = 1.0f - std::exp(-CURSOR_LERP_SPEED * deltaTime);
                m_smoothX += (targetX - m_smoothX) * alpha;
                m_smoothY += (targetY - m_smoothY) * alpha;

                QCursor::setPos(qRound(m_smoothX), qRound(m_smoothY));
            }
            cManager->resetCursorUpdate();
        }
    }
    else
    {
        cManager->resetCursorUpdate();
    }
    // ---------------------------------------------------------------
    if (cManager->justShot())
    {
        rManager->setHit(false);
        if (weapon && weapon->cooldownReady())
        {
            if (weapon->canShoot()) // a des munitions
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
            else
            {
                weapon->restartShootTimer(); // respecte le cooldown même à 0 munitions
            }
        }
        // Toujours consommer le pending shot, que le cooldown soit prêt ou non
        // Sinon les tirs s'accumulent pendant un rechargement et partent en rafale après
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
    gManager->update(deltaTime, {});
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
    // Synchroniser les balles avec la valeur recue de l'Arduino
    if (weapon && cManager->getMunition() >= 0)
        weapon->setCurrentAmmo(cManager->getMunition());
    if (weapon)
        gManager->getPlayer()->getWeapon()->updatePowerUp();
    rManager->setPowerUpActive(weapon ? weapon->isPoweredUp() : false);

    // Mettre à jour le compteur de balles dans le HUD
    if (weapon) {
        int ammo = weapon->getCurrentAmmo();
        if (uiManager->getGamePage()->amoEdit())
            uiManager->getGamePage()->amoEdit()->setText(QString::number(ammo));
        uiManager->updateBalles(ammo);
    }
}


ControllerManager* Engine::getcManager() const
{
    return cManager;
}

UIManager* Engine::getuiManager() const
{
    return uiManager;
}
