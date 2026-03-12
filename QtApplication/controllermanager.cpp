/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Controller.cpp
Description: Code for the Controller class managing player input.
Modifications:
*/

#include "controllermanager.h"

ControllerManager::ControllerManager()
{
    mFront = false;
    mBack = false;
    mLeft = false;
    mRight = false;
    rRight = false;
    rLeft = false;
}

ControllerManager::~ControllerManager()
{

}

void ControllerManager::keyPressedEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_W) mFront = true;
    if (event->key() == Qt::Key_S) mBack = true;
    if (event->key() == Qt::Key_A) mLeft = true;
    if (event->key() == Qt::Key_D) mRight = true;
    if (event->key() == Qt::Key_Q) rLeft = true;
    if (event->key() == Qt::Key_E) rRight = true;
    if (event->key() == Qt::Key_F)
    {
        shoot = true;
        m_justShot = true;
    }
    if(event->key() == Qt::Key_R)
    {
        m_justReload = true;
    }
}

void ControllerManager::keyReleasedEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_W) mFront = false;
    if (event->key() == Qt::Key_S) mBack = false;
    if (event->key() == Qt::Key_A) mLeft = false;
    if (event->key() == Qt::Key_D) mRight = false;
    if (event->key() == Qt::Key_Q) rLeft = false;
    if (event->key() == Qt::Key_E) rRight = false;
    if (event->key() == Qt::Key_F) shoot = false;
}

