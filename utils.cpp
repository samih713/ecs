#include "ecs.hpp"
#include "utils.hpp"
#include "EntityManager.hpp"

Vector2 util::randomVector(Vector2 maxminX, Vector2 maxminY)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> xDist(maxminX.x, maxminX.y);
    std::uniform_int_distribution<int> yDist(maxminY.x, maxminY.y);
    return Vector2{
        .x = (float)xDist(gen),
        .y = (float)yDist(gen),
    };
}

void util::drawpos(Vector2 pos)
{
    char buff[256];
    snprintf(buff, 256, "[%.2f, %.2f]", pos.x, pos.y);
    DrawText(buff, pos.x + 20, pos.y, 15, BLACK);
}

void util::unloadTextures()
{
    for (auto e : m_entities.getEntities())
    {
        debug("Unloading Textures");
        if (e->cShape)
            UnloadTexture(e->cShape->sprite);
    }
}