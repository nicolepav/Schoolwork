#include "elf.h"

// Elf Implementation

cs_creature::Elf::Elf() { }

cs_creature::Elf::Elf(int s, int hp):cs_creature::Creature(s, hp) { } 

std::string cs_creature::Elf::getSpecies() const { return "Elf"; }

int cs_creature::Elf::getDamage() const {
    int damage = cs_creature::Creature::getDamage();
    if ((rand() % 2) == 0) {
        std::cout << "Magical attack inflicts " << damage << " additional damage points!" << std::endl;
        damage *= 2;
    }
    return damage;
}
