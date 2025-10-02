#include "ecs.hpp"
#include "EntityManager.hpp"
#include "system.hpp"
#include "game.hpp"

EntityManager m_entities;


int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE);
    SetTargetFPS(30);


    while (!WindowShouldClose())
    {
        BeginDrawing();
            game::manageEnemies();
            ClearBackground(RAYWHITE);
            systems::render(m_entities.getEntities());
            systems::duration_despawn(m_entities.getEntities());
        EndDrawing();
        m_entities.update();
    }
    util::unloadTextures();
    CloseWindow();
}
