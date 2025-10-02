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
            const auto &duration = e->cDuration;
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
            util::drawPos(Vector2{dst.x + 5.0f, dst.y + 5.0f});
            if (duration) {
                util::drawDuration(Vector2{dst.x + 5.0f, dst.y + 25.0f}, duration->m_birth);
            }
        }
    }
    static void duration_despawn(const entity_vec_t &entities)
    {
        auto now = high_resolution_clock::now();
        for (const auto &e : entities)
        {
            const auto &duration = e->cDuration;
            if (!duration)
                continue;
            if (duration->m_birth + duration->m_timeAlive < now)
                e->m_alive = false;
        }
    }
};

#endif // SYSTEM_HPP