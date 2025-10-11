#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "Entity.hpp"

using std::make_shared;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

class EntityManager
{
public:
    void init();
    void update();
    shared_ptr<Entity> addEntity(const string &tag);
    vector<shared_ptr<Entity>> &getEntities();
    vector<Entity> &getEntities(const string &);

private:
    vector<shared_ptr<Entity>> m_entities;
    map<string, vector<shared_ptr<Entity>>> m_entityMap;
    vector<shared_ptr<Entity>> m_toAdd;
};

#endif // ENTITY_MANAGER_HPP