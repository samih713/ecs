#include <algorithm>

#include "EntityManager.hpp"

using std::remove_if;

shared_ptr<Entity> EntityManager::addEntity(const string &tag)
{
    static size_t id = 0;

    auto e = shared_ptr<Entity>(new Entity(id++, tag));
    m_toAdd.push_back(e);
    return e;
}

vector<shared_ptr<Entity>> &EntityManager::getEntities()
{
    return m_entities;
}

vector<shared_ptr<Entity>> &EntityManager::getEntities(const string &t)
{
    return m_entityMap.at(t);
}

static void removeDeadEntities(vector<shared_ptr<Entity>> v)
{
    auto isDead = [](shared_ptr<Entity> e)
    {
        return !e->isActive();
    };
    if (v.empty()) return;
    v.erase(remove_if(v.begin(), v.end(), isDead));
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    removeDeadEntities(m_entities);
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}
