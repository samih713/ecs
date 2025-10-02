#include "ecs.hpp"
#include "EntityManager.hpp"
#include "game.hpp"
#include "utils.hpp"

void game::spawnEnemy()
{
    constexpr int SHORTEST_ALIVE = 1;
    constexpr int LONGEST_ALIVE = 8;
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
    int timeAlive = util::randomFloat(SHORTEST_ALIVE, LONGEST_ALIVE) + 0.5;
    e->cDuration = std::make_shared<CDuration>(std::chrono::seconds(timeAlive));
}

void game::manageEnemies()
{
    constexpr size_t MAX_ENEMIES = 3;
    auto &enemies = m_entities.getEntities("enemy");
    size_t enemyCount = enemies.size();
    for (size_t i = enemies.size(); i < MAX_ENEMIES; ++i)
    {
        game::spawnEnemy();
    }
}
