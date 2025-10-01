#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

#include "ecs.hpp"

namespace util
{

    Vector2 randomVector(Vector2 maxminX, Vector2 maxminY);
    void drawpos(Vector2 pos);
    void unloadTextures();

};

#endif //  UTILS_HPP