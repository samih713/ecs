#include "EntityManager.hpp"

int main() {
    EntityManager em;
    auto &entities = em.get_entites();
    auto &transforms = em.get_transforms();

    entity_id_t player_id = em.create_player();
    em.destroy(player_id);

    for (auto &e : entities) {
        std::cout << e << std::endl;
    }
    for (auto &t : transforms) {
        std::cout << t;
    }
}


/*

[6] [6] [6] [6] [6] [6]

*/