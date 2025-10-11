#include "Entity.hpp"

#if 1 // delete
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
#endif 

Entity::Entity(const string &tag) : m_tag(tag)
{
    // cout << m_tag + " entity created" << endl;
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