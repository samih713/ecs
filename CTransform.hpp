#include <raylib.h>

#ifndef CTRANSFORM_HPP
#define CTRANSFORM_HPP

struct CTransform {
    Vector2 pos;
    Vector2 vel;
    // CTransform &operator=(const CTransform &&o) = delete;
};

// debug
static std::ostream &operator<<(std::ostream &os, CTransform t) {
    os << std::endl;
    os << "position / [ " << t.pos.x << " , " << t.pos.y << " ]\n";
    os << "velocity / [ " << t.vel.x << " , " << t.vel.y << " ]\n";
    os << std::endl;
    return os;
}

#endif // CTRANSFORM_HPP