#include <iostream>
#include <memory>
#include <vector>
#include <random>

#include <raylib.h>

#define UNUSED(x) ((void)x)
#define DEBUG(msg) (std::cerr << (msg) << std::endl)
/* -------------------------------------------------------------------------- */
/*                               WINDOW CONSTATS                              */
/* -------------------------------------------------------------------------- */
#define SCREEN_W 1080
#define SCREEN_H 720
/* -------------------------------------------------------------------------- */
/*                              PLAYER_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
#define PLAYER_SPRITE ("assets/ship.png")
#define PLAYER_INITIAL_X (SCREEN_W / 2)
#define PLAYER_INITIAL_Y (SCREEN_H - 20)
#define PLAYER_INITIAL_U (0.0f)
#define PLAYER_INITIAL_V (0.0f)
#define PLAYER_W (100)
#define PLAYER_H (100)
/* -------------------------------------------------------------------------- */
/*                               ENEMY_CONSTANTS                              */
/* -------------------------------------------------------------------------- */
#define ENEMY_SPRITE ("assets/enemy.png")
#define LOWER_Y_BOUND (SCREEN_H / 2)
#define ENEMY_INITIAL_U (0.0f)
#define ENEMY_INITIAL_V (0.0f)
#define ENEMY_W (75)
#define ENEMY_H (75)
/* -------------------------------------------------------------------------- */
/*                                 COMPONENTS                                 */
/* -------------------------------------------------------------------------- */
enum class CTYPE
{
    TRANSFORM,
    SPRITE,
    _COUNT,
    _NOTFOUND,
};

class Component
{
public:
    Component(CTYPE t) : _type(t)
    {
        DEBUG("Component created.");
    }
    virtual ~Component() {};

    virtual void print() const = 0;
    CTYPE getType() const { return _type; }

private:
    CTYPE _type;
};

class CTransform : public Component
{
public:
    CTransform(int x, int y, int u, int v) : Component(CTYPE::TRANSFORM), _x(x), _y(y), _u(u), _v(v)
    {
        DEBUG("Positon Created.");
    };

    void print() const override
    {
        std::cout << "\n--- CTransform ---\n";
        std::cout << "Position: [" << _x << ", " << _y << "]\n";
        std::cout << "Velocity: [" << _u << ", " << _v << "]\n";
        std::cout << std::endl;
    }

    int _x;
    int _y;
    int _u;
    int _v;
};

class CSprite : public Component
{
public:
    CSprite(const char *sprite_path, Vector2 size) : Component(CTYPE::SPRITE), sprite_path(sprite_path)
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

    void print() const override
    {
        std::cout << "\n--- Sprite ---\n";
        std::cout << "sprite path: " << sprite_path << std::endl;
        std::cout << "size: [" << dest.width << ", " << dest.height << "]\n";
    }

    const char *sprite_path;
    Texture2D sprite;
    Rectangle src;
    Rectangle dest;
    Vector2 origin;
};

/* -------------------------------------------------------------------------- */
/*                                    ENTIY                                   */
/* -------------------------------------------------------------------------- */
class Entity
{
public:
    ~Entity() {};

    std::shared_ptr<Component> getComponent(CTYPE t)
    {
        for (auto c : _components)
        {
            if (c->getType() == t)
                return c;
        }
        throw std::runtime_error("Component Not found!");
    }

    static std::shared_ptr<Entity> createEntity()
    {
        return std::shared_ptr<Entity>(new Entity());
    }

    void add_component(std::shared_ptr<Component> c)
    {
        _components.push_back(c);
    };

private:
    Entity()
    {
        DEBUG("Entity created.");
    };
    std::vector<std::shared_ptr<Component>> _components;
};

struct Vec2
{
    int x;
    int y;
};

Vec2 generate_random_position(Vec2 xBounds, Vec2 yBounds)
{
    // setup
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution xDist(xBounds.x, xBounds.y);
    std::uniform_int_distribution yDist(yBounds.x, yBounds.y);

    return Vec2{
        .x = xDist(gen),
        .y = yDist(gen),
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
        player->add_component(std::make_shared<CTransform>(PLAYER_INITIAL_X, PLAYER_INITIAL_Y, PLAYER_INITIAL_U, PLAYER_INITIAL_V));
        player->add_component(std::make_shared<CSprite>(PLAYER_SPRITE, playerSize));
        // add to vector
        _entities.push_back(player);
        return (*player);
    }

    Entity &createEnemy()
    {
        auto enemy = Entity::createEntity();
        // position
        Vector2 enemySize{.x = PLAYER_W, .y = PLAYER_H};
        Vec2 pos = generate_random_position(Vec2{0, SCREEN_W}, Vec2{0, LOWER_Y_BOUND});
        // add components
        enemy->add_component(std::make_shared<CTransform>(pos.x, pos.y, ENEMY_INITIAL_U, ENEMY_INITIAL_V));
        enemy->add_component(std::make_shared<CSprite>(ENEMY_SPRITE, enemySize));
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
            auto t = std::dynamic_pointer_cast<CTransform>(e->getComponent(CTYPE::TRANSFORM));
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
        CTYPE type = CTYPE::SPRITE;
        for (auto e : _entites)
        {
            auto s = std::dynamic_pointer_cast<CSprite>(e->getComponent(type));
            auto t = std::dynamic_pointer_cast<CTransform>(e->getComponent(CTYPE::TRANSFORM));
            draw(*t, *s);
        }
    }

private:
    static void draw(CTransform &t, CSprite &s)
    {
        s.dest.x = t._x;
        s.dest.y = t._x;
        DrawTexturePro(s.sprite, s.src, s.dest, s.origin, 0, WHITE);
    }
};

/* -------------------------------------------------------------------------- */
/*                                    MAIN                                    */
/* -------------------------------------------------------------------------- */
int main()
{
    EntityManager em;

    auto &_entites = em.get_entites();

    InitWindow(SCREEN_W, SCREEN_H, "Gamer");
    SetTargetFPS(60);

    Entity player = em.createPlayer();
    Entity e1 = em.createEnemy();
    Entity e2 = em.createEnemy();

    while (!WindowShouldClose())
    {
        SMovement::move(_entites);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        SRender::render(_entites);
        EndDrawing();
    }
}