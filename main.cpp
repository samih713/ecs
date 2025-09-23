#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <typeinfo>
#include <random>
#include <math.h>
#include <map>
#include <optional>

#include "raylib.h"
#include "raymath.h"

#define UNUSED(x) ((void)x)
#define DEBUG(msg) (std::cerr << (msg) << std::endl)
/* -------------------------------------------------------------------------- */
/*                               WINDOW CONSTATS                              */
/* -------------------------------------------------------------------------- */
#define SCREEN_W 1280
#define SCREEN_H 720
/* -------------------------------------------------------------------------- */
/*                              PLAYER_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
static const char *PLAYER_SPRITE = "assets/ship.png";
static const float PLAYER_W = 75;
static const float PLAYER_H = 75;
static const float PLAYER_INITIAL_X = SCREEN_W / 2;
static const float PLAYER_INITIAL_Y = SCREEN_H - (PLAYER_H / 2.0f) - /*offset*/ 30;
static const float PLAYER_INITIAL_U = 2.0f;
static const float PLAYER_INITIAL_V = 0.0f;
/* -------------------------------------------------------------------------- */
/*                               ENEMY_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
static const char *ENEMY_SPRITE = "assets/enemy.png";
static const float ENEMY_W = 50.0f;
static const float ENEMY_H = 50.0f;
static const float UPPER_Y_BOUND = (ENEMY_H / 2.0f) + /*offset*/ 30;
static const float LOWER_Y_BOUND = SCREEN_H / 2.0f;
static const float ENEMY_INITIAL_U = 0.0f;
static const float ENEMY_INITIAL_V = 0.5f;
/* -------------------------------------------------------------------------- */
/*                                oritentation                                */
/* -------------------------------------------------------------------------- */
#define RIGHT (90)
#define UP (0)
#define LEFT (270)
#define DOWN (180)
/* -------------------------------------------------------------------------- */
/*!                             FORWARD DECLARATION                          !*/
/* -------------------------------------------------------------------------- */
class Entity;
class SInput;
/* -------------------------------------------------------------------------- */
/*                                 COMPONENTS                                 */
/* -------------------------------------------------------------------------- */

class Component
{
public:
    virtual ~Component() {};
};

class CTransform : public Component
{
public:
    CTransform(float x, float y, float u, float v) : _x(x), _y(y), _u(u), _v(v) {};
    float _x;
    float _y;
    float _u;
    float _v;
};

class CSprite : public Component
{
public:
    CSprite(const char *sprite_path, Vector2 size, int orientation) : spritePath(sprite_path), orientation(orientation)
    {
        // load the sprite
        sprite = LoadTexture(sprite_path);
        if (!IsTextureValid(sprite))
        {
            throw std::runtime_error("Invalid Texture!");
        }
        // set src
        src = (Rectangle){.x = 0.0f, .y = 0.0f, .width = (float)sprite.width, .height = (float)sprite.height};
        // set dest
        dest = (Rectangle){.x = 0, .y = 0, .width = size.x, .height = size.y};
        // set origin
        origin = (Vector2){.x = dest.width / 2.0f, .y = dest.height / 2.0f};
    }

    const char *spritePath;
    Texture2D sprite;
    Rectangle src;
    Rectangle dest;
    float orientation;
    Vector2 origin;
};

// change to a command with a map of keys and commands(functions) mapping
class CCommand : public Component
{
public:
    CCommand() {};
    ~CCommand() {};

    std::function<void(std::shared_ptr<Entity>)> getCommand(int key)
    {
        auto command = keybinds.find(key);
        if (command != keybinds.end())
        {
            return command->second;
        }
        return nullptr;
    };

    void addKeybind(int key, std::function<void(std::shared_ptr<Entity>)> command)
    {
        auto result = keybinds.insert({key, command});
        if (!result.second)
            throw std::runtime_error("Keybind already exists");
    }

private:
    std::map<int, std::function<void(std::shared_ptr<Entity>)>> keybinds;
};

class CCollison : public Component
{
public:
    CCollison(bool collided) : collided(collided) {};
    ~CCollison() {};

    bool collided;
};

/* -------------------------------------------------------------------------- */
/*                                    ENTIY                                   */
/* -------------------------------------------------------------------------- */

class Entity
{
public:
    ~Entity() {};

    template <class T>
    std::shared_ptr<T> get()
    {
        for (auto c : _components)
        {
            if (std::dynamic_pointer_cast<T>(c))
                return std::dynamic_pointer_cast<T>(c);
        }
        return nullptr;
    }

    static std::shared_ptr<Entity> createEntity()
    {
        return std::shared_ptr<Entity>(new Entity());
    }

    template <typename T>
    void addComponent(std::shared_ptr<T> c)
    {
        _components.push_back(c);
    };

private:
    std::vector<std::shared_ptr<Component>> _components;

    Entity() {
    };
};

Vector2 generatePosition(Vector2 xBounds, Vector2 yBounds)
{
    // setup
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> xDist(xBounds.x, xBounds.y);
    std::uniform_int_distribution<int> yDist(yBounds.x, yBounds.y);

    return Vector2{
        .x = (float)xDist(gen),
        .y = (float)yDist(gen),
    };
}

class EntityManager
{
public:
    EntityManager() {};
    ~EntityManager() {};

    Entity &createPlayer();

    Entity &createEnemy()
    {
        auto enemy = Entity::createEntity();
        // position
        Vector2 enemySize{.x = PLAYER_W, .y = PLAYER_H};
        Vector2 pos = generatePosition(Vector2{0.0f, (float)SCREEN_W}, Vector2{UPPER_Y_BOUND, LOWER_Y_BOUND});
        // add components
        enemy->addComponent(std::make_shared<CTransform>(pos.x, pos.y, ENEMY_INITIAL_U, ENEMY_INITIAL_V));
        enemy->addComponent(std::make_shared<CSprite>(ENEMY_SPRITE, enemySize, DOWN));
        enemy->addComponent(std::make_shared<CCollison>(false));
        // add to vector
        _entities.push_back(enemy);
        return (*enemy);
    }

    Entity &createBullet(Vector2 &dir, Vector2 &pos)
    {
        static std::vector<std::shared_ptr<Entity>> bullets;

        static float radius = 3.0f;
        static Color color = BLUE;

        // DrawCircle(x, y, radius, COLOR);
        auto bullet = Entity::createEntity();
        // add components
        bullet->addComponent(std::make_shared<CTransform>(pos.x, pos.y, dir.x, dir.y));
        // add to vector
        _entities.push_back(bullet); 
        return (*bullet);
    }

    void destroy(std::shared_ptr<Entity> e)
    {
        _entities.erase((std::find(_entities.begin(), _entities.end(), e)));
    }

    std::vector<std::shared_ptr<Entity>> &get_entites()
    {
        return _entities;
    }

private:
    std::vector<std::shared_ptr<Entity>> _entities;
};
/* ------------------------- ENTITY MANAGER CREATED ------------------------- */
EntityManager em;

/* -------------------------------------------------------------------------- */
/*                               MOVEMENT SYSTEM                              */
/* -------------------------------------------------------------------------- */

class SMovement
{
public:
    static void move(std::vector<std::shared_ptr<Entity>> &_entites)
    {
        for (auto e : _entites)
        {
            auto t = e->get<CTransform>();
            auto cc = e->get<CCommand>();
            if (t && !cc)
                update(*t);
        }
    }

private:
    static void update(CTransform &t)
    {
        t._x += t._u;
        t._y += t._v;
        t._x = Clamp(t._x, 0, SCREEN_W);
        t._y = Clamp(t._y, 0, SCREEN_H);
    }
};

/* -------------------------------------------------------------------------- */
/*                              RENDERING SYSTEM                              */
/* -------------------------------------------------------------------------- */

class SRender
{
public:
    static void render(std::vector<std::shared_ptr<Entity>> &_entites)
    {
        for (auto e : _entites)
        {
            auto s = e->get<CSprite>();
            auto t = e->get<CTransform>();
            if (s && t)
                draw(*t, *s);
        }
    }

private:
    static void draw(CTransform &t, CSprite &s)
    {
        char buffer[256];
        s.dest.x = t._x;
        s.dest.y = t._y;
        sprintf(buffer, "[%.2f, %.2f]", s.dest.x, s.dest.y);
        DrawTexturePro(s.sprite, s.src, s.dest, s.origin, s.orientation, WHITE);
        DrawText(buffer, s.dest.x + 20, s.dest.y + 20, 20, BLACK);
    }
};

/* -------------------------------------------------------------------------- */
/*                                INPUT SYSTEM                                */
/* -------------------------------------------------------------------------- */

std::vector<int> pressedKeys;
class SInput
{
public:
    static std::shared_ptr<Entity> getPlayer(std::vector<std::shared_ptr<Entity>> &_entites)
    {
        for (auto e : _entites)
        {
            if (e->get<CCommand>())
                return e;
        }
        return nullptr;
    }
    static void process(std::vector<std::shared_ptr<Entity>> &_entites)
    {
        static auto player = getPlayer(_entites);
        if (player)
            playerMouseRotate(player);
        for (auto k : pressedKeys)
        {
            for (auto e : _entites)
            {
                auto cc = e->get<CCommand>();
                if (cc)
                {
                    auto command = cc->getCommand(k);
                    if (command)
                    {
                        if (!IsKeyDown(k))
                            pressedKeys.erase(std::find(pressedKeys.begin(), pressedKeys.end(), k));
                        command(e);
                    }
                }
            }
        }
    }

    static void registerKeyPresses()
    {
        int key;
        while (key = GetKeyPressed())
        {
            pressedKeys.push_back(key);
        }
    }

    static void playerMoveLeft(std::shared_ptr<Entity> e)
    {
        auto t = e->get<CTransform>();
        t->_x -= t->_u;
        t->_x = Clamp(t->_x, 0, SCREEN_W);
    }

    static void playerMoveRight(std::shared_ptr<Entity> e)
    {
        auto t = e->get<CTransform>();
        t->_x += t->_u;
        t->_x = Clamp(t->_x, 0, SCREEN_W);
    }

    static void playerShoot(std::shared_ptr<Entity> e)
    {
        auto t = e->get<CTransform>();
        Vector2 dir = {t->_u, t->_v};
        Vector2 pos = {t->_x, t->_y};
        em.createBullet(dir, pos);
        DrawText("Pew Pew!!", t->_x + 30, t->_y - 35, 20, BLACK);
    }

    static void playerRotateLeft(std::shared_ptr<Entity> e)
    {
        auto s = e->get<CSprite>();
        s->orientation += 1;
        s->orientation = Clamp(s->orientation, -90.0f, 90.0f);
    }

    static void playerRotateRight(std::shared_ptr<Entity> e)
    {
        auto s = e->get<CSprite>();
        s->orientation -= 1;
        s->orientation = Clamp(s->orientation, -90.0f, 90.0f);
    }

    static void playerMouseRotate(std::shared_ptr<Entity> e)
    {
        auto t = e->get<CTransform>();
        auto s = e->get<CSprite>();
        Vector2 mouse = GetMousePosition();
        Vector2 player = {t->_x, t->_y};
        Vector2 direction = Vector2Subtract(mouse, player);
        float angle = atan2f(direction.y, direction.x) * RAD2DEG;

        // DEBUG
        char buffer[256] = {0};
        sprintf(buffer, "[%.2f]", angle);
        DrawText(buffer, mouse.x, mouse.y, 30, BLACK);
        s->orientation = angle + 90;
    }
    // command functions
    /*
        keybinds
        Q - move player left
        E - move player right
        W - Shoot
        A - Rotate left
        D - Rotate right
    */
};

class SCollision
{
    bool check_collisions(std::vector<std::shared_ptr<Entity>> &_entites)
    {
        for (auto e : _entites)
        {
            auto col = e->get<CCollison>();
            if (col)
            {
                return true;
            }
        }
        return false;
    }
};

Entity &EntityManager::createPlayer()
{
    auto player = Entity::createEntity();
    Vector2 playerSize{.x = PLAYER_W, .y = PLAYER_H};
    // add components
    player->addComponent(std::make_shared<CTransform>(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, PLAYER_INITIAL_U, PLAYER_INITIAL_V));
    player->addComponent(std::make_shared<CSprite>(PLAYER_SPRITE, playerSize, UP));
    player->addComponent(std::make_shared<CCollison>(false));
    // player keybinds
    std::shared_ptr<CCommand> c = std::make_shared<CCommand>();
    player->addComponent(c);
    c->addKeybind(KEY_A, SInput::playerMoveLeft);
    c->addKeybind(KEY_D, SInput::playerMoveRight);
    c->addKeybind(KEY_W, SInput::playerShoot);
    // add to vector
    _entities.push_back(player);
    return (*player);
}
/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */

int main()
{

    auto &_entites = em.get_entites();

    SetTraceLogLevel(LOG_ERROR);

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_W, SCREEN_H, "Gamer");
    SetTargetFPS(60);

    ShowCursor();

    Entity player = em.createPlayer();
    Entity e1 = em.createEnemy();
    Entity e2 = em.createEnemy();
    Entity e3 = em.createEnemy();
    Entity e5 = em.createEnemy();
    Entity e6 = em.createEnemy();

    while (!WindowShouldClose())
    {
        SInput::registerKeyPresses();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        SRender::render(_entites);
        SInput::process(_entites);
        SMovement::move(_entites);
        EndDrawing();
    }
}