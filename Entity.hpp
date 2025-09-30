#include "ecs.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
    Entity(const string &tag, size_t id) : m_tag(tag), m_id(id) { debug("created entity!"); }
    /* ------------------------------- components ------------------------------- */
    shared_ptr<CTransform> cTransform = nullptr;
    shared_ptr<CName> cName = nullptr;
    shared_ptr<CShape> cShape = nullptr;
    shared_ptr<CBBox> cBBox = nullptr;
    /* ----------------------------- getters/setters ---------------------------- */
    size_t id() const { return m_id; }
    const string &tag() const { return m_tag; }
    bool isAlive() { return m_alive; }
    void kill() {m_alive = false;}

private:
    const size_t m_id = 0;
    const string m_tag = "Default";
    bool m_alive = true;
};

std::ostream &operator<<(std::ostream &os, const Entity &e)
{
    os << "[" << e.tag() << "_" << e.id() << "]";
    return os;
}

#endif // ENTITY_HPP