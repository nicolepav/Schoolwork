#include "cyberdemon.h"

// Cyberdemon Implementation

cs_creature::Cyberdemon::Cyberdemon() { }
cs_creature::Cyberdemon::Cyberdemon(int s, int hp):cs_creature::Demon(s, hp) { }

std::string cs_creature::Cyberdemon::getSpecies() const { return "Cyberdemon"; }