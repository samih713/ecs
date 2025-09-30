#include "Entity.hpp"

std::ostream &operator<<(std::ostream &os, const Entity &e)
{
    os << "[" << e.m_tag << "_" << e.m_id << "]";
    return os;
}