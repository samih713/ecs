#include "Game.hpp"
#include "Systems.hpp"
#include "Utility.hpp"
#include "Components.hpp"

static CShape randShape()
{
    float radius = Utility::random(20.0f, 100.0f);
    float thickness = Utility::random(5.0f, 25.0f);
    int sides = Utility::random<int>(3, 9);
    int color = Utility::random<int>(0, INT32_MAX);
    Color outline = {
        .r = static_cast<unsigned char>(color << 0),
        .g = static_cast<unsigned char>(color << 8),
        .b = static_cast<unsigned char>(color << 16),
        .a = 255,
    };
    return (CShape){
        radius, thickness, sides, outline};
}

static CTransform randTransform()
{
    float x = Utility::random(0, 300);
    float y = Utility::random(0, 300);
    float u = Utility::random(0, 20);
    float v = Utility::random(0, 20);
    float angle = Utility::random(0, 360);

    Vector2 pos{x, y};
    Vector2 vel{u, v};

    return (CTransform){pos, vel, angle};
}

void Game::spawnEnemy()
{
    auto enemy = m_entites.addEntity("enemy");
    enemy->cShape = make_shared<CShape>(randShape());
    enemy->cTransform = make_shared<CTransform>(randTransform());
}


void Game::update() {
    m_entites.update();
    const auto &entities = m_entites.getEntities();
    System::render(entities);
}