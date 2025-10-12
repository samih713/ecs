#if 1 // delete
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
#endif

#include <raylib.h>
#include <raymath.h>

#include "Game.hpp"

int main()
{
    InitWindow(1920, 1080, "Circle");

    Game game;
    game.spawnEnemy();
    game.spawnEnemy();
    game.spawnEnemy();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.update();
        EndDrawing();
    }
    CloseWindow();
}