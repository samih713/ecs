#ifndef ECS_HPP
#define ECS_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <raylib.h>
#include <raymath.h>

// Usings
using std::cerr;
using std::cout;
using std::endl;
using std::make_shared;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;


// Debug helpers
static inline void debug(const string &msg)
{
#if defined(__DEBUG__)
    std::cerr << "[DEBUG]: " << msg << std::endl;
#endif
}

// Window Constants
static constexpr int WINDOW_W = 980;
static constexpr int WINDOW_H = 640;
static constexpr const char *WINDOW_TITLE = "goty";
// Game Constants
static constexpr float ENEMY_WIDTH = 100.0f;
static constexpr float ENEMY_HEIGHT = 100.0f;
static constexpr float ENEMY_SPAWN_X_OFFSET = WINDOW_W * 0.05f + ENEMY_WIDTH;
static constexpr float ENEMY_SPAWN_Y_OFFSET = WINDOW_H * 0.05f + ENEMY_HEIGHT;
static constexpr Vector2 ENEMY_SPAWN_X_VEC{.x = ENEMY_SPAWN_X_OFFSET, .y = WINDOW_W - ENEMY_SPAWN_X_OFFSET};
static constexpr Vector2 ENEMY_SPAWN_Y_VEC{.x = ENEMY_SPAWN_Y_OFFSET, .y = WINDOW_H * 0.5f};
static constexpr Vector2 ENEMY_VELOCITY{.x = 0.0f, .y = 100.0f};
static constexpr float ENEMY_ROTATION = 180;

#endif // ECS_HPP