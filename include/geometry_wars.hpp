#ifndef GEOMETRY_WARS_HPP
#define GEOMETRY_WARS_HPP

#include <assert.h>

static constexpr int SCREEN_W = 720;
static constexpr int SCREEN_H = 480;
// enemy
static constexpr int ENEMY_MAX_SIDES = 9;
static constexpr int ENEMY_MIN_SIDES = 0;

static constexpr float ENEMY_MAX_RADIUS = 50;
static constexpr float ENEMY_MIN_RADIUS = 10;

static constexpr float ENEMY_MAX_THICKNESS = 9;
static constexpr float ENEMY_MIN_THICKNESS = 3;

static constexpr float ENEMY_MAX_U = 5;
static constexpr float ENEMY_MAX_V = 5;

static constexpr float ENEMY_MAX_COUNT = 15;

/* ----------------------------------- DEV ---------------------------------- */
#define TODO (assert(false && "NOT YET IMPLEMENTED!!"))
#define UNUSED(x) ((void)(x))

#endif // GEOMETRY_WARS_HPP