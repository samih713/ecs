#include "Systems.hpp"
#include "Game.hpp"


void System::render(const vector<shared_ptr<Entity>> &entities)
{
    for (const auto &e : entities)
    {
        auto &t = e->cTransform;
        auto &s = e->cShape;
        if (!t || !s)
            continue;
        DrawPolyLinesEx(t->pos, s->sides, s->radius, t->angle, s->thickness, s->outline);
    }
}