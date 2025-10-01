#include "ecs.hpp"
#include "EntityManager.hpp"
#include "system.hpp"
#include "game.hpp"

EntityManager m_entities;


int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE);
    SetTargetFPS(120);

    game::spawnEnemy();
    game::spawnEnemy();
    m_entities.update();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            systems::render(m_entities.getEntities());
        EndDrawing();
    }
    util::unloadTextures();
    CloseWindow();
}
