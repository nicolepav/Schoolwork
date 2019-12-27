#include "creature.h"

// Creature Implementation

cs_creature::Creature::Creature() {
    strength = 10;
    hitpoints = 10;
}

cs_creature::Creature::Creature(int newStrength, int newHitpoints )
    : strength(newStrength), hitpoints(newHitpoints) { }

// All Creatures inflict damage which is a random number up to their strength
int cs_creature::Creature::getDamage() const {
    int damage;
    damage = (rand() % strength) + 1;
    std::cout << getSpecies() << " attacks for " << damage << " points!" << std::endl;
    return damage;
}

int cs_creature::Creature::getStrength() const { return strength; }
int cs_creature::Creature::getHP() const { return hitpoints; }

void cs_creature::Creature::setStrength(int s) { strength = s; }
void cs_creature::Creature::setHP(int hp) { hitpoints = hp; }
