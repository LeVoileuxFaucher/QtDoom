/*
Author: Mathieu Vincent
Date: Febuary 12, 2026
File name: Painter.h
Goal: Header file for the wall renderer
Modifications:
*/

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QColor>
#include <QTimer>

#include "geostructs.h"
#include "Actor.h"
#include "bsp.h"

class RenderManager
{

public:
    RenderManager(QGraphicsScene* scene, int screenWidth, int screenHeight);

    void renderWall(const Linedef& wall, const std::vector<Vertex>& verteces, const Actor& player);

    void render(Actor m_player, Actor m_enemy, BSP* bsp, const std::vector<Vertex>& verteces);
    void renderActor(const Actor m_actor, const Actor m_player, QColor color);
    std::vector<Linedef> getRenderedWalls();
    void renderRay(float targetScreenX, float targetScreenY, int frames);
    float projectHeight(float worldHeight, float distance);
    Vertex coordPlayer(const Vertex& point, const Actor& player);
    QGraphicsView* getView() const;
    void renderGun();
    void updateScreenSize(int width, int height);

    void setHit(bool h) {hit = h;}
    void setPowerUpActive(bool active) { m_isPowerUpActive = active; }

private:
    QGraphicsScene* m_scene;
    int m_screenWidth;
    int m_screenHeight;
    float m_focalLength;
    float distanceMin;
    std::vector<Linedef> renderedWalls;
    int m_rayFramesLeft = 0;
    float m_rayTargetX = 0;
    float m_rayTargetY = 0;
    float m_rayStartX = 0;
    float m_rayStartY = 0;
    bool hit = false;
    QPixmap m_wallTexture;
    bool m_isPowerUpActive = false;




    bool clipWall(Vertex& p1, Vertex& p2);

    Vertex projectToScreen(const Vertex& cameraPoint);




};

#endif // RENDERMANAGER_H
