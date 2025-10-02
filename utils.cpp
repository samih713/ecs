#include "ecs.hpp"
#include "utils.hpp"
#include "EntityManager.hpp"

float util::randomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

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

void util::drawPos(Vector2 pos)
{
    char buff[256];
    snprintf(buff, 256, "[%.2f, %.2f]", pos.x, pos.y);
    DrawText(buff, pos.x + 20, pos.y, 15, BLACK);
}

void util::drawDuration(Vector2 pos, time_point<high_resolution_clock> birth)
{
    char buff[256];
    auto elapsed = std::chrono::duration_cast<duration<float>>(high_resolution_clock::now() - birth);
    snprintf(buff, 256, "(%.1f s)", elapsed.count());
    DrawText(buff, pos.x + 20, pos.y, 25, BLACK);
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