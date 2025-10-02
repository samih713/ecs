#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>
#include <chrono>

#include "ecs.hpp"
#include "CDuration.hpp"

namespace util
{

    float randomFloat(float min, float max);
    Vector2 randomVector(Vector2 maxminX, Vector2 maxminY);
    void drawPos(Vector2 pos);
    void drawDuration(Vector2 pos, time_point<high_resolution_clock> birth);
    void unloadTextures();

};

#endif //  UTILS_HPP