#include "EntityManager.hpp"

#define PLAYER_INITIAL_X (800/2)
#define PLAYER_INITIAL_Y (400 - 50)

entity_id_t EntityManager::create_player() {
    // player transform
    Vector2 pos{PLAYER_INITIAL_X, PLAYER_INITIAL_Y};
    Vector2 vel{0, 0};
    CTransform transform{pos, vel};
    // register it
    _entities.at(_current_id) = _current_id;  // add it in the next available slot
    // add it's components
    _transforms.at(_current_id) = std::move(transform);
    // increment current id
    _current_id++;

    return --_current_id;
}

// move to another file later
void EntityManager::destroy(entity_id_t id) {
    _entities.at(id) = NO_ENTITY;
}