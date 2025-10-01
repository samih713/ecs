#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "utils.hpp"

namespace systems
{
    static void render(const entity_vec_t &entitites)
    {
        for (const auto &e : entitites)
        {
            const auto &shape = e->cShape;
            const auto &transform = e->cTransform;
            if (!shape || !transform)
            {
                continue;
            }
            const auto &dst = shape->dst;
            const auto &src = shape->src;
            const auto &sprite = shape->sprite;
            const auto &origin = shape->origin;
            const auto &rotation = transform->rotation;
            DrawTexturePro(sprite, src, dst, origin, rotation, WHITE);
            util::drawpos(Vector2{dst.x + 5.0f, dst.y + 5.0f});
        }
    }
};

#endif // SYSTEM_HPP