#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <raylib.h>

#include "Utility.hpp"

struct CTransform
{
    Vector2 pos = {0.0f, 0.0f};
    Vector2 velocity = {0.0f, 0.0f};
    float angle = 0;

    CTransform(const Vector2 &p, const Vector2 &v, float a)
        : pos(p), velocity(v), angle(a)
    {
    }
};

struct CShape
{
    float radius, thickness;
    int sides;
    Color outline;
    CShape(float radius, float thickness, int sides, const Color &outline)
        : radius(radius), thickness(thickness), sides(sides), outline(outline) {}
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