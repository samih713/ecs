#include "ecs.hpp"
#include "EntityManager.hpp"
#include "game.hpp"
#include "utils.hpp"

void game::spawnEnemy()
{

    auto e = m_entities.addEntity("enemy");
    auto enemyPosition = util::randomVector(ENEMY_SPAWN_X_VEC, ENEMY_SPAWN_Y_VEC);
    auto enemyVelocity = Vector2{
        .x = 0,
        .y = 100,
    };

    auto enemySize = Rectangle{
        .x = enemyPosition.x,
        .y = enemyPosition.y,
        .width = ENEMY_WIDTH,
        .height = ENEMY_HEIGHT,
    };

    e->cTransform = std::make_shared<CTransform>(enemyPosition, enemyVelocity, ENEMY_ROTATION);
    e->cShape = std::make_shared<CShape>("./assets/enemy.png", enemySize);
}

