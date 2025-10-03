#include "ecs.hpp"
#include "EntityManager.hpp"
#include "game.hpp"
#include "utils.hpp"

void GameEngine::spawnEnemy()
{
    auto e = m_entities.addEntity("enemy");

    // Transform
    auto enemyPosition = util::randomVector(ENEMY_SPAWN_X_VEC, ENEMY_SPAWN_Y_VEC);
    auto enemyVelocity = Vector2{
        .x = 0,
        .y = 100,
    };
    e->cTransform = std::make_shared<CTransform>(enemyPosition, enemyVelocity, ENEMY_ROTATION);

    // Sprite
    auto enemySize = Rectangle{
        .x = enemyPosition.x,
        .y = enemyPosition.y,
        .width = ENEMY_WIDTH,
        .height = ENEMY_HEIGHT,
    };
    e->cShape = std::make_shared<CShape>("./assets/enemy.png", enemySize);

    // Alive
    constexpr int SHORTEST_ALIVE = 1;
    constexpr int LONGEST_ALIVE = 8;
    int timeAlive = util::randomFloat(SHORTEST_ALIVE, LONGEST_ALIVE) + 0.5;
    e->cDuration = std::make_shared<CDuration>(std::chrono::seconds(timeAlive));
}

void GameEngine::sEnemySpawner()
{
    constexpr size_t MAX_ENEMIES = 3;
    auto &enemies = m_entities.getEntities("enemy");
    size_t enemyCount = enemies.size();
    for (size_t i = enemies.size(); i < MAX_ENEMIES; ++i)
    {
        GameEngine::spawnEnemy();
    }
}
