#include "balrog.h"

// Balrog Implementation

cs_creature::Balrog::Balrog() { }
cs_creature::Balrog::Balrog(int s, int hp):cs_creature::Demon(s, hp) { }

std::string cs_creature::Balrog::getSpecies() const { return "Balrog"; }

// Balrogs are so fast they get to attack twice
int cs_creature::Balrog::getDamage() const {
    int damage = cs_creature::Creature::getDamage();
    int damage2 = (rand() % getStrength()) + 1;
    std::cout << "Balrog speed attack inflicts " << damage2 << " additional damage points!" << std::endl;
    damage += damage2;
    return damage;
}
