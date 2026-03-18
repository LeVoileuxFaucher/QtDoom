/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Controller.cpp
Description: Code for the Controller class managing player input.
Modifications:
*/

#include "controllermanager.h"

ControllerManager::ControllerManager(QObject *parent)
    : QObject(parent)
{
    m_serial = new SerialController(this);
    m_serial->openPort();

    connect(m_serial, &SerialController::moveFront, this, &ControllerManager::moveFront);
    connect(m_serial, &SerialController::moveBack, this, &ControllerManager::moveBack);
    connect(m_serial, &SerialController::moveLeft, this, &ControllerManager::moveLeft);
    connect(m_serial, &SerialController::moveRight, this, &ControllerManager::moveRight);

    connect(m_serial, &SerialController::shoot, this, &ControllerManager::shooting);
    connect(m_serial, &SerialController::reload, this, [this]() { reload(true); });

    connect(m_serial, &SerialController::updateCursor, this, &ControllerManager::updateCursor);
    connect(m_serial, &SerialController::updateMunition, this, &ControllerManager::updateMunition);
    connect(m_serial, &SerialController::updateEncodeur, this, &ControllerManager::updateEncodeur);
    connect(m_serial, &SerialController::boutonEncodeurPressed, this, [this](bool active) {
        if (active) emit confirmSig();
    });
}



ControllerManager::~ControllerManager()
{

}

void ControllerManager::moveFront(bool active) { aFront = active; }
void ControllerManager::moveBack(bool active)  { aBack  = active; }
void ControllerManager::moveLeft(bool active)  { aLeft  = active; }
void ControllerManager::moveRight(bool active) { aRight = active; }

void ControllerManager::shooting(bool active) {
    shoot = active;
    if (active)
    {
        shoot = true;
        if (m_munitionCount > 0)
        {
            m_pendingShots++;
            //qDebug() << "shoot" << m_pendingShots;
        }
    }
}
void ControllerManager::reload(bool active) {
    m_justReload = true;
}

void ControllerManager::updateCursor(int x, int y) {
    m_cursorRawX = x;
    m_cursorRawY = y;
    m_cursorUpdated = true;
}
void ControllerManager::updateMunition(int value) {
    m_munitionCount = value;
}
void ControllerManager::updateEncodeur(int value) {
    if (m_lastEncodeur == -1) {
        m_lastEncodeur = value;
        return;
    }
    if (value != m_lastEncodeur) {
        m_lastEncodeur = value;
        emit potTurnedSig();
        emit potStopedSig();
    }
}




void ControllerManager::keyPressedEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_W) kFront = true;
    if (event->key() == Qt::Key_S) kBack = true;
    if (event->key() == Qt::Key_A) kLeft = true;
    if (event->key() == Qt::Key_D) kRight = true;
    if (event->key() == Qt::Key_Q) rLeft = true;
    if (event->key() == Qt::Key_E) rRight = true;
    if (event->key() == Qt::Key_F)
    {
        shoot = true;
        if (m_munitionCount > 0)
            m_pendingShots++;
    }
    if(event->key() == Qt::Key_R)
    {
        m_justReload = true;
    }
    if(event->key() == Qt::Key_P)
    {
        m_powerUp = true;
    }
    if (event->key() == Qt::Key_Escape)
    {
        potTurns = true;
        potTurnedEvent();
    }
    if (event->key() == Qt::Key_Return)
    {
        mReturn = true;
        shootPressedEvent();
    }
    if(event->key() == Qt::Key_L)
    {
        toggleCursorMode();
    }
}

void ControllerManager::keyReleasedEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_W) kFront = false;
    if (event->key() == Qt::Key_S) kBack = false;
    if (event->key() == Qt::Key_A) kLeft = false;
    if (event->key() == Qt::Key_D) kRight = false;
    if (event->key() == Qt::Key_Q) rLeft = false;
    if (event->key() == Qt::Key_E) rRight = false;
    if (event->key() == Qt::Key_F) shoot = false;
    if (event->key() == Qt::Key_P) m_powerUp = false;
    if (event->key() == Qt::Key_Escape)
    {
        potTurns = false;
        potStopedEvent();
    }
    if (event->key() == Qt::Key_Return)
    {
        mReturn = false;
        shootReleasedEvent();
    }
}

void ControllerManager::potTurnedEvent()
{
    //qDebug() << "pot turned";
    emit potTurnedSig();
}

void ControllerManager::potStopedEvent()
{
    //qDebug() << "pot stoped";
    emit potStopedSig();
}

void ControllerManager::shootPressedEvent()
{
    //qDebug() << "shoot pressed";
    emit shootPressedSig();
}
void ControllerManager::shootReleasedEvent()
{
    //qDebug() << "shoot released";
    emit shootReleasedSig();
}

