#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <memory>

#include "Components.hpp"

using std::shared_ptr;
using std::string;

class EntityManager;

class Entity
{
    friend EntityManager;

public:
    void destroy();
    bool isActive();
    const string &tag();
    size_t id();
    // components
    shared_ptr<CTransform> cTransform;
    shared_ptr<CShape> cShape;
    shared_ptr<CCollision> cCollision;
    shared_ptr<CInput> cInput;
    shared_ptr<CScore> cScore;
    shared_ptr<CLifeSpan> cLifeSpan;

private:
    Entity(const size_t id, const string &tag);

    size_t m_id = 0;
    string m_tag = "default";
    bool m_active = true;
};

#endif // ENTITY_HPP