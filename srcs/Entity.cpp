#include "Entity.hpp"

Entity::Entity(const size_t id, const string &tag) : m_id(id), m_tag(tag)
{
}

void Entity::destroy()
{
    m_active = false;
}

bool Entity::isActive()
{
    return m_active;
}
const string &Entity::tag()
{
    return m_tag;
}
size_t Entity::id()
{
    return m_id;
}