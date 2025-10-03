#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ecs.hpp"
#include "CTransform.hpp"
#include "CShape.hpp"
#include "CDuration.hpp"

class Entity
{
public:
    friend class EntityManager;
    /* ------------------------------- components ------------------------------- */
    shared_ptr<CTransform> cTransform = nullptr;
    shared_ptr<CShape> cShape = nullptr;
    shared_ptr<CDuration> cDuration = nullptr;
    // shared_ptr<CName> cName = nullptr;
    // shared_ptr<CBBox> cBBox = nullptr;
    /* ---------------------------- memeber variables --------------------------- */
    const size_t m_id = 0;
    const string m_tag = "Default";
    bool m_alive = true;

private:
    Entity(const string &tag, size_t id);
};

std::ostream &operator<<(std::ostream &os, const Entity &e);

#endif // ENTITY_HPP