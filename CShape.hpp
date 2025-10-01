#ifndef CSHAPE_HPP
#define CSHAPE_HPP

#include "ecs.hpp"

struct CShape
{
    CShape() = default;
    CShape(const char *spritePath, Rectangle dst_) : dst(dst_)
    {
        sprite = LoadTexture(spritePath);
        if (!IsTextureValid(sprite))
        {
            throw std::runtime_error("Invalid texture");
        }
        float width = sprite.width;
        float height = sprite.height;
        src = Rectangle{
            .x = 0,
            .y = 0,
            .width = width,
            .height = height,
        };
        origin = Vector2{
            .x = dst.width / 2,
            .y = dst.height / 2,
        };
    }
    CShape(const CShape &o) = default;
    ~CShape() { UnloadTexture(sprite); }
    Rectangle src, dst;
    Vector2 origin;
    Texture2D sprite;
};

#endif // CSHAPE_HPP