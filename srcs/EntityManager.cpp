#include "EntityManager.hpp"

void EntityManager::update()
{
    // add pending entites
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

}

shared_ptr<Entity> EntityManager::addEntity(const string &tag)
{
    auto e = shared_ptr<Entity>(new Entity(tag));
    m_toAdd.push_back(e);
    return e;
}

vector<shared_ptr<Entity>> &EntityManager::getEntities() {
    return m_entities;
}