#include "EntityManager.hpp"

EntityManager em;

#if 1 // delete
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
#endif 

int main() {
    em.addEntity("player");
    em.update();
    for (auto &e: em.getEntities()) {
        cout << e->tag() << endl;
    }

}