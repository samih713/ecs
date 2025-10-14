#if 1 // delete
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
#endif

#include <raylib.h>
#include <raymath.h>

#include "geometry_wars.hpp"
#include "Game.hpp"

int main()
{
    InitWindow(SCREEN_W, SCREEN_H, "Geometry Wars");
    SetTargetFPS(60);

    Game game;
    for (int i = 0; i < 15; ++i)
    {
        game.spawnEnemy();
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.update();
        EndDrawing();
    }
    CloseWindow();
}