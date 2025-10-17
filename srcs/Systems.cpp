
#include "Systems.hpp"
#include "geometry_wars.hpp"

#include <raymath.h>
#include "Game.hpp"

void System::render(const vector<shared_ptr<Entity>> &entities)
{
    for (const auto &e : entities)
    {
        auto &t = e->cTransform;
        auto &s = e->cShape;
        if (!t || !s)
            continue;
        DrawPolyLinesEx(t->pos, s->sides, s->radius, t->rotation, s->thickness, s->outline);
    }
}

void System::movement(const vector<shared_ptr<Entity>> &entities)
{
    for (const auto &e : entities)
    {
        auto &t = e->cTransform;
        if (!t)
            continue;
        t->rotation += 3;
        t->pos = Vector2Add(t->pos, t->velocity);
    }
}

void System::enemy_spawner(const vector<shared_ptr<Entity>> &ememies)
{
    UNUSED(ememies);
    TODO;
}

void System::collision(const vector<shared_ptr<Entity>> &entities)
{
    // check walls collision
    for (const auto &e : entities)
    {
        auto &t = e->cTransform;
        auto &c = e->cCollision;
        if (!t || !c)
            continue;
        // left right up down
        if (t->pos.x - c->radius < 0)
        {
            t->pos.x = c->radius;
            t->velocity.x = -t->velocity.x;
        }

        if (t->pos.x + c->radius > SCREEN_W)
        {
            t->pos.x = SCREEN_W - c->radius;
            t->velocity.x = -t->velocity.x;
        }
        if (t->pos.y - c->radius < 0)
        {
            t->pos.y = c->radius;
            t->velocity.y = -t->velocity.y;
        }

        if (t->pos.y + c->radius > SCREEN_H)
        {
            t->pos.y = SCREEN_H - c->radius;
            t->velocity.y = -t->velocity.y;
        }
    }
}