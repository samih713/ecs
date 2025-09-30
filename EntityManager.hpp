#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "ecs.hpp"


class EntityManager
{
public:
    /* ---------------------------------- meta ---------------------------------- */
    EntityManager() = default;
    entity_vec_t &getEntities() { return m_entities; }
    entity_vec_t &getEntities(const string &tag) { return m_entityMap[tag]; }
    void update();
    /* ---------------------------- entity management --------------------------- */
    shared_ptr<Entity> addEntity(const string &tag);
    void destroy(Entity &e);
    /* -------------------------------- entities -------------------------------- */

private:
    entity_vec_t m_entities;
    entity_vec_t m_toAdd;
    tag_map_t m_entityMap;
    size_t m_totalEntities = 0;
    /* ---------------------------- helper functions ---------------------------- */
    void _commitEntities();
    void _removeEntities();
};

#endif // ENTITY_MANAGER_HPP