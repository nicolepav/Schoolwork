#ifndef BALROG_H
#define BALROG_H

#include "demon.h"

namespace cs_creature {
    class Balrog : public cs_creature::Demon {
        public:
            Balrog();
            Balrog(int s, int hp);
            std::string getSpecies() const;
            int getDamage() const;

    };
}

#endif