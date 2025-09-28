#include "EntityManager.hpp"

int main() {
    EntityManager em;
    auto entities = em.get_entites();
    auto transforms = em.get_transforms();

    em.create_player();

    for (auto &e : entities) {
        std::cout << e << std::endl;
    }
    for (auto &t : transforms) {
        std::cout << t;
    }
}
