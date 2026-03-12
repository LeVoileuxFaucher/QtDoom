/*
Author: Mathieu Vincent
Date: Febuary 12, 2026
File name: Painter.cpp
Goal: Code for rendering walls.
Modifications:
*/


#include "rendermanager.h"
#include <QColor>
#include <algorithm>
#include <cmath>


RenderManager::RenderManager(QGraphicsScene* scene, int screenWidth, int screenHeight)
{
    m_focalLength = screenWidth / 2.0f;
    distanceMin = 0.1f;

    m_scene = scene;
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}


void RenderManager::renderWall(const Linedef& wall, const std::vector<Vertex>& verteces, const Actor& player)
{
    Vertex p1 = coordPlayer(verteces[wall.start], player);
    Vertex p2 = coordPlayer(verteces[wall.end], player);

    if (!clipWall(p1, p2))
        return;

    Vertex screen1 = projectToScreen(p1);
    Vertex screen2 = projectToScreen(p2);

    float height1_floor = projectHeight(0, p1.y); // wall.floorHeight, p1.y);
    float height1_ceil  = projectHeight(10, p1.y); // wall.ceilingHeight, p1.y);

    float height2_floor = projectHeight(0, p2.y); // wall.floorHeight, p2.y);
    float height2_ceil  = projectHeight(10, p2.y); // wall.ceilingHeight, p2.y);

    QPolygonF polygon;
    polygon << QPointF(screen1.x, height1_ceil)
            << QPointF(screen2.x, height2_ceil)
            << QPointF(screen2.x, height2_floor)
            << QPointF(screen1.x, height1_floor);

    QGraphicsPolygonItem* wallItem = m_scene->addPolygon(polygon);

    float avgDistance = (p1.y + p2.y) / 2.0f;
    int brightness = std::max(0, std::min(255,
                                          (int)(255.0f / (1.0f + avgDistance / 10.0f))));

    wallItem->setBrush(QColor(brightness, brightness, brightness));
    wallItem->setPen(Qt::NoPen);
}



Vertex RenderManager::coordPlayer(const Vertex& point, const Actor& player)
{
    Vertex playerPos = player.getPosition();
    float anglePlayer = player.getAngle();

    float dx = point.x - playerPos.x;
    float dy = point.y - playerPos.y;

    float cosAngle = std::cos(-anglePlayer);
    float sinAngle = std::sin(-anglePlayer);

    Vertex camera;
    camera.x = dx * cosAngle - dy * sinAngle;
    camera.y = dx * sinAngle + dy * cosAngle;

    return camera;
}



bool RenderManager::clipWall(Vertex& p1, Vertex& p2)
{
    if (p1.y < distanceMin && p2.y < distanceMin)
        return false;

    if (p1.y < distanceMin)
    {
        float t = (distanceMin - p1.y) / (p2.y - p1.y);
        p1.x = p1.x + t * (p2.x - p1.x);
        p1.y = distanceMin;
    }

    if (p2.y < distanceMin)
    {
        float t = (distanceMin - p2.y) / (p1.y - p2.y);
        p2.x = p2.x + t * (p1.x - p2.x);
        p2.y = distanceMin;
    }

    return true;
}


Vertex RenderManager::projectToScreen(const Vertex& cameraPoint)
{
    Vertex screen;
    screen.x = (cameraPoint.x / cameraPoint.y) * m_focalLength
               + m_screenWidth / 2.0f;
    screen.y = 0;
    return screen;
}


float RenderManager::projectHeight(float worldHeight, float distance)
{
    float eyeHeight = 2.5f;

    float relativeHeight = worldHeight - eyeHeight;

    float screenHeight = (relativeHeight / distance) * m_focalLength;

    return m_screenHeight / 2.0f - screenHeight;
}


void RenderManager::renderActor(Actor actor, const Actor player, QColor color)
{
    if (actor.getHealth() == 0) return;
    Vertex camPos = coordPlayer(actor.getPosition(), player);


    if (camPos.y < distanceMin)
        return;


    float screenX = (camPos.x / camPos.y) * m_focalLength + m_screenWidth / 2.0f;


    float spriteHeight = (1.0f / camPos.y) * m_focalLength;
    float spriteWidth  = spriteHeight * 2.0f;



    float actorHeight = 5.0f;
    float eyeHeight   = 3.5f;
    float spriteBottom = projectHeight(0.0f, camPos.y);
    float spriteTop    = projectHeight(actorHeight, camPos.y);
    float squareSize   = spriteBottom - spriteTop;

    QRectF spriteRect(
        screenX - squareSize / 2.0f,
        spriteTop,
        squareSize,
        squareSize
        );

    if (spriteRect.right() < 0 || spriteRect.left() > m_screenWidth)
        return;


    int brightness = std::max(0, std::min(255,
                                          (int)(255.0f / (1.0f + camPos.y / 10.0f))));
    QColor shadedColor(
        color.red()   * brightness / 255,
        color.green() * brightness / 255,
        color.blue()  * brightness / 255
        );


    QGraphicsRectItem* spriteItem = m_scene->addRect(spriteRect);
    spriteItem->setBrush(shadedColor);
    spriteItem->setPen(Qt::NoPen);
}

void RenderManager::renderRay(float mouseScreenX, float mouseScreenY,
                              float targetScreenX, float targetScreenY, int frames)
{
    m_rayFramesLeft = frames;
    m_rayStartX = mouseScreenX;
    m_rayStartY = mouseScreenY;
    m_rayTargetX = targetScreenX;
    m_rayTargetY = targetScreenY;
}

// UTILISEE POUR EXEMPLE
void RenderManager::render(Actor m_player, Actor m_enemy, BSP* bsp, const std::vector<Vertex>& verteces)
{
    m_scene->clear();
    bsp->traverse(m_player.getPosition(), renderedWalls, verteces);

    for (const Linedef& wall : renderedWalls) {
        renderWall(wall, verteces, m_player);
    }
    renderActor(m_enemy, m_player, QColor(255,0,0));

    if (m_rayFramesLeft > 0)
    {
        float startX = m_screenWidth / 2.0f;
        float startY = m_screenHeight / 2.0f;
        m_scene->addLine(m_rayStartX, m_rayStartY, m_rayTargetX, m_rayTargetY,
                         QPen(QColor(255, 255, 0), 3));
        m_rayFramesLeft--;
    }
}

std::vector<Linedef> RenderManager::getRenderedWalls()
{
    return renderedWalls;
}

QGraphicsView* RenderManager::getView() const
{
    if (m_scene && !m_scene->views().isEmpty())
        return m_scene->views().first();
    return nullptr;
}
