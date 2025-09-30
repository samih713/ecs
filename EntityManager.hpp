#include "ecs.hpp"

#include "Entity.hpp"

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

using entity_vec_t = std::vector<std::shared_ptr<Entity>>;
using tag_map_t = std::map<string, entity_vec_t>;

class EntityManager
{
public:
    EntityManager() {};
    entity_vec_t &getEntitites() { return m_entities; };
    entity_vec_t &getEntitites(const string &tag) { return m_entityMap[tag]; };
    shared_ptr<Entity> addEntity(const string &tag);
    void update();

private:
    entity_vec_t m_entities;
    entity_vec_t m_toAdd;
    tag_map_t m_entityMap;
    size_t m_totalEntities = 0;
};

shared_ptr<Entity> EntityManager::addEntity(const string &tag)
{
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    for (auto it = m_entities.begin(); it != m_entities.end(); it++) // for range fails here since end changes
    {
        auto &e = *it;
        entity_vec_t &tagVector = m_entityMap[e->tag()];
        m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](auto e){return !e->isAlive();}), m_entities.end());
        tagVector.erase(std::remove_if(tagVector.begin(), tagVector.end(), [](auto e){return !e->isAlive();}), tagVector.end());
    }
    m_toAdd.clear();
}

#endif // ENTITY_MANAGER_HPP