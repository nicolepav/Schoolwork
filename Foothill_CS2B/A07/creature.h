#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>

namespace cs_creature {

    class Creature {
        private:
            int strength; 
            int hitpoints;   
        public:
            Creature();                                     
            Creature(int newStrength, int newHitpoints);
            
            virtual int getDamage() const;          
            virtual std::string getSpecies() const = 0;      
            
            int getStrength() const;
            int getHP() const;

            void setStrength(int s);
            void setHP(int hp);
    
    };

}



#endif