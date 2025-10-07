#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <raylib.h>

struct CTransform
{
    Vector2 pos, speed, scale;
    double angle;
};
struct CShape
{
    Color fill, outline;
    int points;
    float radius, thickness;
};
struct CCollision
{
    float radius = 0;
};
struct CInput
{
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;
};
struct CScore
{
    int score = 0;
};
struct CLifeSpan
{
    int remaining = 0;
    int total = 0;
};

#endif // COMPONENTS_HPP