#include "Entity.hpp"

Entity::Entity(const string &tag, size_t id) : m_tag(tag), m_id(id) { debug("created entity!"); }

std::ostream &operator<<(std::ostream &os, const Entity &e)
{
    os << "[" << e.m_tag << "_" << e.m_id << "]";
    return os;
}