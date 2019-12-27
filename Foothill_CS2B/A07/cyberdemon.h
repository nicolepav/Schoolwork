#ifndef CYBERDEMON_H
#define CYBERDEMON_H

#include "demon.h"

namespace cs_creature {
    class Cyberdemon : public cs_creature::Demon {
        public:
            Cyberdemon();
            Cyberdemon(int s, int hp);
            std::string getSpecies() const;
    };
}

#endif