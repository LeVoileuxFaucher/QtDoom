/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Engine.h
Description: Header file for the game engine handling all events.
Modifications:
*/

#ifndef ENGINE_H
#define ENGINE_H

#include<QObject>
#include<QTimer>
#include<QElapsedTimer>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QDebug>
#include<QPoint>

#include"controllermanager.h"
#include"gamemanager.h"
#include"rendermanager.h"
#include"uimanager.h"

#define TARGET_FPS 60

class Engine : public QObject{
    Q_OBJECT
private:
    ControllerManager *cManager;
    GameManager *gManager;
    RenderManager *rManager;
    UIManager *uiManager;

    // To operate the frames
    QTimer timer;
    QElapsedTimer elapsedTimer;
    float deltaTime = 0.0f;

    int m_width;
    int m_height;
    QWidget* m_widget;

    QGraphicsScene* m_scene;
    QGraphicsView*  m_view;


    static constexpr int CURSOR_MIN = 0;
    static constexpr int CURSOR_MAX = 255;

    float m_smoothX = -1.0f;
    float m_smoothY = -1.0f;

    static constexpr float CURSOR_LERP_SPEED = 6.0f;


    static constexpr int   BORDER_ZONE       = 40;

    static constexpr float BORDER_ROT_SPEED  = 1.2f;

public:
    Engine(QGraphicsScene *scene, int width, int height, QObject *parent, QGraphicsView *view);
    ~Engine();
    void gameLoop();
    ControllerManager* getcManager() const;
    UIManager* getuiManager() const;

public slots:
    void start();
    void pauseGame();
    void resumeGame();
    void restartGame();
    void quitGame();
    void gameOver();
};

#endif
