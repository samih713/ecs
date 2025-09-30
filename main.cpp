#include "ecs.hpp"
#include "EntityManager.hpp"

int main()
{
    EntityManager em;
    auto player0 = em.addEntity("player");
    auto player1 = em.addEntity("player");
    auto player2 = em.addEntity("player");
    auto player3 = em.addEntity("player");
    auto player4 = em.addEntity("player");

    em.update();

    auto &entityVector = em.getEntitites();

    for (auto &e : entityVector)
    {
        cout << *e << endl;
    }
    cout << "\n\n------------------------\n\n"; 
    player1->kill();
    em.update();

    for (auto &e : entityVector)
    {
        cout << *e << endl;
    }
    return 0;
}
