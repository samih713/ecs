#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <vector>
#include <memory>

#include "Entity.hpp"

using std::vector;
using std::shared_ptr;

namespace System
{
    void movemnt();
    void user_input();
    void render(const vector<shared_ptr<Entity>> &entities);
    void enemy_spawner();
    void collision();
};

#endif // SYSTEMS_HPP