#include "ecs.hpp"
#include "system.hpp"

EntityManager m_entities;

void spawnEnemy()
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


int main()
{
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE);
    SetTargetFPS(120);

    m_entities.update();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            systems::render(m_entities.getEntities());
        EndDrawing();
    }
}
