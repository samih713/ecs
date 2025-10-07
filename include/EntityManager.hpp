#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "Entity.hpp"

using std::vector;
using std::map;
using std::string;
using std::shared_ptr;

class EntityManager {
    public:
        void init();
        void update();
        shared_ptr<Entity> addEntity(...);
        vector<Entity> &getEntities();
        vector<Entity> &getEntities(const string &);
    private:
        vector<Entity> m_entities;
        map<string, Entity> m_entityMap;
        vector<Entity> m_toAdd;

};

#endif // ENTITY_MANAGER_HPP