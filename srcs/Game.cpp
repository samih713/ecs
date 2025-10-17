#include "geometry_wars.hpp"
#include "Game.hpp"
#include "Systems.hpp"
#include "Utility.hpp"
#include "Components.hpp"

static CShape randShape()
{
    float radius = Utility::random(ENEMY_MIN_RADIUS, ENEMY_MAX_RADIUS);
    float thickness = Utility::random(ENEMY_MIN_THICKNESS, ENEMY_MAX_THICKNESS);
    int sides = Utility::random<int>(ENEMY_MIN_SIDES, ENEMY_MAX_SIDES);
    int color = Utility::random<int>(0, INT32_MAX);
    Color outline = {
        .r = static_cast<unsigned char>(color >> 0 & 0xFF),
        .g = static_cast<unsigned char>(color >> 8 & 0xFF),
        .b = static_cast<unsigned char>(color >> 16 & 0xFF),
        .a = 255,
    };
    return (CShape){
        radius, thickness, sides, outline};
}

static CTransform randTransform()
{
    float x = Utility::random(0, SCREEN_W);
    float y = Utility::random(0, SCREEN_H);
    float u = Utility::random(-ENEMY_MAX_U, ENEMY_MAX_U);
    float v = Utility::random(-ENEMY_MAX_V, ENEMY_MAX_V);
    int rotation = Utility::random(0, 360);

    Vector2 pos{x, y};
    Vector2 vel{u, v};

    return (CTransform){pos, vel, rotation};
}

void Game::spawnEnemy()
{
    auto enemy = m_entites.addEntity("enemy");
    enemy->cShape = make_shared<CShape>(randShape());
    enemy->cTransform = make_shared<CTransform>(randTransform());
    enemy->cCollision = make_shared<CCollision>(enemy->cShape->radius);
}

void Game::update()
{
    m_entites.update();
    const auto &entities = m_entites.getEntities();

    System::render(entities);
    System::movement(entities);
    System::collision(entities);
}