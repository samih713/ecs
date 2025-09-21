#include <iostream>
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
#define SCREEN_W 1980
#define SCREEN_H 1080
/* -------------------------------------------------------------------------- */
/*                              PLAYER_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
static const char*  PLAYER_SPRITE = "assets/ship.png";
static const float PLAYER_W = 75;
static const float PLAYER_H = 75;
static const float PLAYER_INITIAL_X = SCREEN_W / 2;
static const float PLAYER_INITIAL_Y = SCREEN_H - (PLAYER_H / 2.0f) - /*offset*/30;
static const float PLAYER_INITIAL_U = 0.0f;
static const float PLAYER_INITIAL_V = 0.0f;
/* -------------------------------------------------------------------------- */
/*                               ENEMY_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
static const char*  ENEMY_SPRITE = "assets/enemy.png";
static const float  ENEMY_W = 50.0f;
static const float  ENEMY_H = 50.0f;
static const float  UPPER_Y_BOUND = (ENEMY_H / 2.0f) + /*offset*/ 30;
static const float  LOWER_Y_BOUND = SCREEN_H / 2.0f;
static const float  ENEMY_INITIAL_U = 0.0f;
static const float  ENEMY_INITIAL_V = 0.25f;
/* -------------------------------------------------------------------------- */
/*                                oritentation                                */
/* -------------------------------------------------------------------------- */
#define RIGHT (90)
#define UP (0)
#define LEFT (270)
#define DOWN (180)
/* -------------------------------------------------------------------------- */
/*                                 COMPONENTS                                 */
/* -------------------------------------------------------------------------- */
class Component {public:virtual ~Component(){};};
class CTransform : public Component
{
public:
    CTransform(float x, float y, float u, float v) : _x(x), _y(y), _u(u), _v(v)
    {
    };

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
        origin = (Vector2){.x = sprite.width / 2.0f, .y = sprite.height / 2.0f};
    }

    const char *spritePath;
    Texture2D sprite;
    Rectangle src;
    Rectangle dest;
    int orientation;
    Vector2 origin;
};

class CInput : public Component
{
    public:
        CInput(std::vector<int> &keys) : keys(keys){};
        ~CInput() {};
        bool hasKey(int key) {
            for (auto k:keys) {
                if (k == key)
                    return true;
                return false;
            }
        }

    std::vector<int> keys;
};

/* -------------------------------------------------------------------------- */
/*                                    ENTIY                                   */
/* -------------------------------------------------------------------------- */
class Entity
{
public:
    ~Entity() {};

    template<class T>
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

    template<typename T>
    void addComponent(std::shared_ptr<T> c)
    {
        _components.push_back(c);
    };

private:
    std::vector<std::shared_ptr<Component>> _components;

    Entity()
    {
        DEBUG("Entity created.");
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

    Entity &createPlayer()
    {
        auto player = Entity::createEntity();
        Vector2 playerSize{.x = PLAYER_W, .y = PLAYER_H};
        // add components
        player->addComponent(std::make_shared<CTransform>(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, PLAYER_INITIAL_U, PLAYER_INITIAL_V));
        player->addComponent(std::make_shared<CSprite>(PLAYER_SPRITE, playerSize, UP));
        // player keybinds
        std::vector<int> keybinds;
        keybinds.push_back(KEY_A);
        keybinds.push_back(KEY_D);
        player->addComponent(std::make_shared<CInput>(keybinds));
        // add to vector
        _entities.push_back(player);
        return (*player);
    }

    Entity &createEnemy()
    {
        auto enemy = Entity::createEntity();
        // position
        Vector2 enemySize{.x = PLAYER_W, .y = PLAYER_H};
        Vector2 pos = generatePosition(Vector2{0.0f, (float)SCREEN_W}, Vector2{UPPER_Y_BOUND, LOWER_Y_BOUND});
        // add components
        enemy->addComponent(std::make_shared<CTransform>(pos.x, pos.y, ENEMY_INITIAL_U, ENEMY_INITIAL_V));
        enemy->addComponent(std::make_shared<CSprite>(ENEMY_SPRITE, enemySize, DOWN));
        // add to vector
        _entities.push_back(enemy);
        return (*enemy);
    }

    std::vector<std::shared_ptr<Entity>> &get_entites()
    {
        return _entities;
    }

private:
    std::vector<std::shared_ptr<Entity>> _entities;
};

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
            if (t)
                update(*t);
        }
    }

private:
    static void update(CTransform &t)
    {
        t._x += t._u;
        t._y += t._v;
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
class SInput
{
    public:
        static void process(std::vector<std::shared_ptr<Entity>> &_entites) {
            for (auto e:_entites) {
                auto i = e->get<CInput>();
                auto t = e->get<CTransform>();
                if (i) {
                    if (IsKeyDown(KEY_D) && i->hasKey(KEY_D)) {
                        t->_u = 10;
                    }
                    if (IsKeyDown(KEY_A) && i->hasKey(KEY_A)) {
                        t->_u = -10;
                    }
                    
                }
            }
        }
};
/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */
int main()
{
    EntityManager em;

    auto &_entites = em.get_entites();

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_W, SCREEN_H, "Gamer");
    SetTargetFPS(60);

    Entity player = em.createPlayer();
    Entity e1 = em.createEnemy();
    Entity e2 = em.createEnemy();
    Entity e3 = em.createEnemy();
    Entity e5 = em.createEnemy();
    Entity e6 = em.createEnemy();

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            SRender::render(_entites);
            SInput::process(_entites);
            SMovement::move(_entites);
        EndDrawing();
    }
}