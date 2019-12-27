#ifndef HUMAN_H
#define HUMAN_H

#include "creature.h"

namespace cs_creature {
    class Human : public cs_creature::Creature {
        public:
            Human();
            Human(int s, int hp);
            std::string getSpecies() const;
    };
}

#endif