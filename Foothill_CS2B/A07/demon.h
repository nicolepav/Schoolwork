#ifndef DEMON_H
#define DEMON_H

#include "creature.h"

namespace cs_creature {
    class Demon : public cs_creature::Creature {
        public:
            Demon();
            Demon(int s, int hp);
            std::string getSpecies() const;
            int getDamage() const;
    };
}


#endif


