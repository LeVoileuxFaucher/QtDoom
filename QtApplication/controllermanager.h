/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Controller.h
Description: Header file for the Controller class. This class handles the inputs from the player.
Modifications:
*/

#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include<QObject>
#include<QKeyEvent>
#include "serialcontroller.h"
#include <QDebug>

class ControllerManager : public QObject{
    Q_OBJECT
public:
    ControllerManager(QObject *parent = nullptr);
    ~ControllerManager();
    SerialController* m_serial;
    bool movingFront(){return kFront || aFront;}
    bool movingBack(){return kBack  || aBack;}
    bool movingLeft(){return kLeft  || aLeft;}
    bool movingRight(){return kRight || aRight;}
    bool rotatingLeft(){return rLeft;}
    bool rotatingRight(){return rRight;}
    bool isShooting() {return shoot;}

    bool justShot()    { return m_pendingShots > 0; }
    void resetShot()   { if (m_pendingShots > 0) m_pendingShots--; }

    bool isReloading() {return m_justReload; }
    void resetReload() {m_justReload = false;}

    bool isPowerUp()   {return m_powerUp;}
    void resetPowerUp(){m_powerUp = false;}
    int getMunition() const { return m_munitionCount; }
    int getEncodeurAmmo() const { return m_munitionCount; }

    // Curseur Arduino (valeurs brutes 0-255)
    int getCursorRawX() const { return m_cursorRawX; }
    int getCursorRawY() const { return m_cursorRawY; }
    bool hasCursorUpdate() const { return m_cursorUpdated; }
    void resetCursorUpdate() { m_cursorUpdated = false; }

    // Mode curseur : true = curseur actif (défaut), false = souris libre
    bool isCursorModeEnabled() const { return m_cursorModeEnabled; }
    void toggleCursorMode() { m_cursorModeEnabled = !m_cursorModeEnabled; }

    // Rotation par bordure (activée par Engine quand le curseur est près du bord)
    bool rotatingLeftBorder()  const { return m_borderRotLeft; }
    bool rotatingRightBorder() const { return m_borderRotRight; }
    void setBorderRotLeft(bool v)  { m_borderRotLeft  = v; }
    void setBorderRotRight(bool v) { m_borderRotRight = v; }

private:
    // États clavier (maintenus tant que la touche est enfoncée)
    bool kFront = false;
    bool kBack  = false;
    bool kLeft  = false;
    bool kRight = false;
    // États Arduino (mis à jour à chaque trame série)
    bool aFront = false;
    bool aBack  = false;
    bool aLeft  = false;
    bool aRight = false;
    bool rRight = false;
    bool rLeft  = false;
    bool shoot  = false;
    int  m_pendingShots = 0;
    bool m_justReload = false;
    bool m_powerUp = false;
    bool mReturn;
    bool potTurns;
    int m_munitionCount = -1;
    int m_lastEncodeur = -1;
    int m_cursorRawX = 128;
    int m_cursorRawY = 128;
    bool m_cursorUpdated = false;
    bool m_cursorModeEnabled = true;  // true = mode curseur actif par défaut
    bool m_borderRotLeft  = false;    // rotation gauche déclenchée par bordure
    bool m_borderRotRight = false;    // rotation droite déclenchée par bordure

public slots:
    void keyPressedEvent(QKeyEvent * event);
    void keyReleasedEvent(QKeyEvent * event);
    void potTurnedEvent();
    void potStopedEvent();
    void shootPressedEvent();
    void shootReleasedEvent();

    void moveFront(bool active);
    void moveBack(bool active);
    void moveLeft(bool active);
    void moveRight(bool active);
    void shooting(bool active);
    void reload(bool active);
    void updateCursor(int x, int y);
    void updateMunition(int value);
    void updateEncodeur(int value);

signals:
    void potTurnedSig();
    void potStopedSig();
    void shootPressedSig();
    void shootReleasedSig();
    void confirmSig();
};

#endif
