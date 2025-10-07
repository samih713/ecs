#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>

#include "Entity.hpp"
#include "EntityManager.hpp"

using std::shared_ptr;
using std::string;

class Game {
    public:
        void run();
        void init(const string &config);
        void update();
        // 
        void spawnPlayer();
        void spawnEnemy();
        void spawnSmallEnemy(shared_ptr<Entity> entity);
        void spawnBullet(shared_ptr<Entity> entity, const Vector2 &mousePos);
        void spawnSpecialWeapon(shared_ptr<Entity> entity);
        // systems
    private:
        EntityManager m_entites;
        shared_ptr<Entity> m_player;
        bool m_paused = false;
        bool m_running = true;
        int m_score = 0;
        int m_currentFrame = 0;
        int m_lastEnemySpawnTime = 0;
};


#endif // GAME_HPP