#ifndef ENTITY_MANAGER_HHP
#define ENTITY_MANAGER_HHP

#include <iostream>
#include <vector>
/* ------------------------------- COMPONENTS ------------------------------- */
#include "CTransform.hpp"

// #define MAX_ENTITIES 512
// #define NO_ENTITY 513

#define MAX_ENTITIES 5
#define NO_ENTITY 6

using entity_id_t = u_int16_t;

class EntityManager
{
public:
    /* ------------------------------ CONSTRUCTION ------------------------------ */
    EntityManager() : _entities(MAX_ENTITIES, NO_ENTITY) {} // vector of 512 id's
    ~EntityManager() = default;
    EntityManager(const EntityManager &) = delete;
    EntityManager &operator=(const EntityManager &) = delete;
    EntityManager(const EntityManager &&) = delete;
    EntityManager &operator=(const EntityManager &&) = delete;
    /* ----------------------------------- API ---------------------------------- */
    std::vector<entity_id_t> &get_entites() { return _entities; };
    std::vector<CTransform> &get_transforms() { return _transforms; };
    /* ------------------------------ CREATE ENTITY ----------------------------- */
    entity_id_t create_player();
    entity_id_t create_enemy();
    entity_id_t create_bullet();
    void destroy(entity_id_t id);

private:
    std::vector<entity_id_t> _entities;
    std::vector<CTransform> _transforms;
    entity_id_t _current_id = 0;
    /* ---------------------------- UTILITY FUNCTIONS --------------------------- */
    void _register(entity_id_t id);
};

#endif // ENTITY_MANAGER_HHP