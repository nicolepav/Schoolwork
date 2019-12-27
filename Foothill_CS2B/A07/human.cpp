#include "human.h"

// Human Implemenation

cs_creature::Human::Human() { }
cs_creature::Human::Human(int s, int hp):cs_creature::Creature(s, hp) { 

}
std::string cs_creature::Human::getSpecies() const { return "Human"; }

