#include "EntityManager.hpp"

/* ---------------------------------- meta ---------------------------------- */
entity_vec_t &EntityManager::getEntities()
{
    return m_entities;
}

entity_vec_t &EntityManager::getEntities(const string &tag)
{
    return m_entityMap[tag];
}

void EntityManager::update()
{
    _commitEntities();
    _removeEntities();
}
/* ---------------------------- entity management --------------------------- */
shared_ptr<Entity> EntityManager::addEntity(const string &tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::destroy(Entity &e)
{
    e.m_alive = false;
}
/* ---------------------------- helper functions ---------------------------- */
void EntityManager::_commitEntities()
{
    for (const auto &e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->m_tag].push_back(e);
    }
    m_toAdd.clear();
}

void EntityManager::_removeEntities()
{
    auto isDeadEntity = [](const std::shared_ptr<Entity> &e)
    { return !e->m_alive; };

    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), isDeadEntity),
                     m_entities.end());
    for (auto &t : m_entityMap)
    {
        entity_vec_t &tagVector = t.second;
        tagVector.erase(std::remove_if(tagVector.begin(), tagVector.end(), isDeadEntity), tagVector.end());
    }
}
