#include "EntityManager.hpp"

#define PLAYER_INITIAL_X (800 / 2)
#define PLAYER_INITIAL_Y (400 - 50)

void EntityManager::_register(entity_id_t id)
{
    if (id > MAX_ENTITIES)
        throw std::runtime_error("Max Entites reached");
    _entities.at(id) = id;
}

entity_id_t EntityManager::create_player()
{
    // register new entity
    entity_id_t id = _current_id++; // 0 and _current_id = 1
    _register(id);

    // player transform
    Vector2 pos{PLAYER_INITIAL_X, PLAYER_INITIAL_Y};
    Vector2 vel{100, 100};
    CTransform transform{pos, vel};

    // add it's components
    _transforms.at(id) = transform;

    return id;
}

// move to another file later
void EntityManager::destroy(entity_id_t id)
{
    _entities.at(id) = NO_ENTITY;
    // remove its transform
    _transforms.erase(_transforms.begin() + id);
}