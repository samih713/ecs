#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <chrono>
#include <string>

#include "Entity.hpp"
#include "EntityManager.hpp"

using std::shared_ptr;
using std::string;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::seconds;

class Game
{
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
    time_point<steady_clock> m_lastEnemySpawnTime = steady_clock::now();
};

#endif // GAME_HPP