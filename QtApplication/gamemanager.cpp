#include "gamemanager.h"

GameManager::GameManager() {
    p = new Actor();
    p->setPosition(0.0f, -2.0f);
    p->setAngle(0.0f);

    //temporaire a modifier
    e = new Actor();
    e->setPosition(5.0f,5.0f);
    e->setAngle(0.0f);

    map = new MapReader();

    std::vector<Vertex> verteces;
    std::vector<Linedef> linedefs;
    std::vector<Sector> sectors;
}

void GameManager::restartGame()
{
    p->setPosition(0.0f, 0.0f);
    p->setAngle(0.0f);
    p->getWeapon()->resetGameAmmo();
    p->resetPlayerHealth();
    updateVie();
    //faut aussi replacer les monstres
}

Actor* GameManager::getPlayer()
{
    return p;
}

Actor* GameManager::getEnemy()
{
    return e;
}

void GameManager::loadMap(const std::string& filename)
{
    if (!map->load(filename))
    {
        qDebug() << "ERROR: Failed to load map";
        return;
    }

    verteces = map->getVerteces();
    linedefs = map->getLinedefs();
    sectors = map->getSectors();

    bsp = new BSP();

    m_playerWeapon = new Weapon(1, 1000.0f, 50.0f, 10, 2.5f);
    p->setWeapon(m_playerWeapon);
    bsp->build(linedefs, verteces);
}

BSP* GameManager::getBSP()
{
    return bsp;
}

void GameManager::update(float deltaTime, std::vector<Linedef> renderedWalls)
{
    e->moveEnemy(*p, deltaTime);

    // Collision detection
    for (const Linedef& wall : renderedWalls) {
        float ok = 0;
    }

    // Enemy damage detection
    if (inRadius(p, e))
    {

        if (e->getHealth() == 0) return;

        if(!m_inContact)
        {
            m_inContact = true;
            m_enemyAttackTimer.restart();
            p->takeDamage(1);
            updateVie();
        }
        else if(m_enemyAttackTimer.elapsed() >= m_attackCooldown)
        {
            m_inContact = false;
            p->takeDamage(1);
            updateVie();
            m_enemyAttackTimer.restart();
        }

        if (p->getHealth() < 1)
        {
            //qDebug("Player Dead");
            emit playerDead();
        }
    }
    else
    {
        e->setMovement(true);
        m_inContact = false;
    }
}

bool GameManager::inRadius(Actor* p, Actor* e)
{
    float radius = 4.0f;
    float dx = p->getPosition().x - e->getPosition().x;
    float dy = p->getPosition().y - e->getPosition().y;

    float distance = (dx * dx) + (dy * dy);
    if (distance < (radius * radius)) return true;
    return false;
}

bool GameManager::shoot(QPoint mousePos, QSize screenSize)
{

    Weapon* weapon = p->getWeapon();
    if (!weapon) return false;


    if (!weapon->canShoot())
    {
        qDebug() << "Cooldown pas écoulé";
        return false;
    }

    weapon->shoot();

    float screenW    = screenSize.width();
    float focalLength = screenW / 2.0f;


    float camDirX = (mousePos.x() - screenW / 2.0f) / focalLength;
    float camDirY = 1.0f;
    float len     = std::sqrt(camDirX * camDirX + camDirY * camDirY);
    camDirX /= len;
    camDirY /= len;

    // Convertit la direction caméra en direction monde
    float playerAngle = p->getAngle();
    float cosA        = std::cos(playerAngle);
    float sinA        = std::sin(playerAngle);
    float worldDirX = camDirX * cosA - camDirY * sinA;
    float worldDirY = camDirX * sinA + camDirY * cosA;

    Vertex playerPos  = p->getPosition();


    float maxDistance = weapon->getRange();
    float step        = 0.05f;

    for (float d = 0; d < maxDistance; d += step)
    {
        float rayX = playerPos.x + worldDirX * d;
        float rayY = playerPos.y + worldDirY * d;

        float dx = rayX - e->getPosition().x;
        float dy = rayY - e->getPosition().y;

        if ((dx*dx + dy*dy) < (1.5f * 1.5f))
        {
            qDebug() << "Touché à distance:" << d;
            e->takeDamage(weapon->getDamage());
            return true;
        }
    }

    qDebug() << "Manqué";
    return false;
}

void GameManager::updateVie()
{
    int vie=p->getHealth();
    emit sigUpdateVie(vie);
}

Weapon* GameManager::getWeapon()
{
    return m_playerWeapon;
}
