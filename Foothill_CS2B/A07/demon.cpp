#include "demon.h"

// Demon Implementation

cs_creature::Demon::Demon() {
    setStrength(10);
    setHP(10);
}
cs_creature::Demon::Demon(int s, int hp):cs_creature::Creature(s, hp) { }

std::string cs_creature::Demon::getSpecies() const { return "Demon"; };

// Demons can inflict damage of 50 with a 25% chance
int cs_creature::Demon::getDamage() const {
    int damage = cs_creature::Creature::getDamage();
    if (rand() % 4 == 0) {
        damage = damage + 50;
        std::cout << "Demonic attack inflicts 50 additional damage points!" << std::endl;
    }
    return damage;
}