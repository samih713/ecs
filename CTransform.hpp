#ifndef CTRANSFORM_HPP
#define CTRANSFORM_HPP

#include "ecs.hpp"

struct CTransform
{
    CTransform() = default;
    CTransform(Vector2 pos_, Vector2 vel_, float rotation_) : pos(pos_), vel(vel_), rotation(rotation_) {}
    Vector2 pos;
    Vector2 vel;
    float rotation;
};

#endif // CTRANSFORM_HPP