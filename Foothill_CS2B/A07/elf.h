#ifndef ELF_H
#define ELF_H

#include "creature.h"

namespace cs_creature {
    class Elf : public cs_creature::Creature {
        public:
            Elf();
            Elf(int s, int hp);
            std::string getSpecies() const;
            int getDamage() const;

    };
}


#endif