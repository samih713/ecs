#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <vector>
#include <memory>

#include "Entity.hpp"

using std::vector;
using std::shared_ptr;

namespace System
{
    void movement(const vector<shared_ptr<Entity>> &entities);
    void user_input();
    void render(const vector<shared_ptr<Entity>> &entities);
    void enemy_spawner(const vector<shared_ptr<Entity>> &ememies);
    void collision(const vector<shared_ptr<Entity>> &entities);
};

#endif // SYSTEMS_HPP