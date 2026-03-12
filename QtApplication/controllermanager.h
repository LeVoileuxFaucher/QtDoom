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

class ControllerManager : public QObject{
    Q_OBJECT
public:
    ControllerManager();
    ~ControllerManager();
    bool movingFront(){return mFront;}
    bool movingBack(){return mBack;}
    bool movingLeft(){return mLeft;}
    bool movingRight(){return mRight;}
    bool rotatingLeft(){return rLeft;}
    bool rotatingRight(){return rRight;}
    bool isShooting() {return shoot;}

    bool justShot()    { return m_justShot; }
    void resetShot()   { m_justShot = false; }

    bool isReloading() {return m_justReload; }
    void resetReload() {m_justReload = false;}

    bool isPowerUp()   {return m_powerUp;}
    void resetPowerUp(){m_powerUp = false;}

private:
    bool mFront;
    bool mBack;
    bool mLeft;
    bool mRight;
    bool rRight;
    bool rLeft;
    bool shoot;
    bool m_justShot = false;
    bool m_justReload = false;
    bool m_powerUp = false;

public slots:
    void keyPressedEvent(QKeyEvent * event);
    void keyReleasedEvent(QKeyEvent * event);
};

#endif
