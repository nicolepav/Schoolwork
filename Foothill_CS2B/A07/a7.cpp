#include <ctime>
#include <cstdlib>

#include "creature.h"
#include "demon.h"
#include "cyberdemon.h"
#include "balrog.h"
#include "human.h"
#include "elf.h"


void battleArena(cs_creature::Creature& a, cs_creature::Creature& b);


int main() {
    
    srand(static_cast<unsigned>(time(nullptr)));
    std::cout << std::endl;

	cs_creature::Elf e(50, 50);
	cs_creature::Balrog b(50, 50);
    cs_creature::Human h(20, 20);
    cs_creature::Cyberdemon c(20, 30);

    // Testing Elf Combinations

    battleArena(e, b);
    battleArena(e, h);
    battleArena(e, c);


    // Testing Balrog Combinations

	cs_creature::Balrog b2(50, 50);
    cs_creature::Human h2(20, 20);
    cs_creature::Cyberdemon c2(20, 30);

    battleArena(b2, h2);
    battleArena(b2, c2);

    // Testing Human Combinations

    cs_creature::Human h3(20, 20);
    cs_creature::Cyberdemon c3(20, 30);

    battleArena(h3, c3);

}







void battleArena(cs_creature::Creature& a, cs_creature::Creature& b) {

    std::cout << std::endl;
    std::cout << "The battle begins: "
    << a.getSpecies() << "[" << a.getStrength() << "," << a.getHP() << "]" << " vs " 
    << b.getSpecies() << "[" << b.getStrength() << "," << b.getHP() << "]" << std::endl;
    
    int aAttack, bAttack;

    do {
        aAttack = a.getDamage();
        bAttack = b.getDamage(); 
        
        b.setHP(b.getHP() - aAttack);
        a.setHP(a.getHP() - bAttack);

        if( a.getHP() < 0 && b.getHP() < 0) {
            std::cout << "Tie Match! Both creatures have fainted" << std::endl;
        }
        else if (a.getHP() <= 0 ) {
            std::cout << a.getSpecies() << "(creature 1) has fainted! Match Over!" << std::endl;
        }
        else if (b.getHP() <= 0 ) {
            std::cout << b.getSpecies() << "(creature 2) has fainted! Match Over!" << std::endl;
        }
    }
    while (a.getHP() > 0 && b.getHP() > 0);
    
}







/* Expected Output

Nicole-Pav:A7 nicolepavlovich$ cd "/Users/nicolepavlovich/Desktop/CS_Foothill/A7/" 
&& g++ a7.cpp -o a7 && "/Users/nicolepavlovich/Desktop/CS_Foothill/A7/"a7

The battle begins: Elf[50,50] vs Balrog[50,50]
Elf attacks for 19 points!
Balrog attacks for 50 points!
Balrog speed attack inflicts 34 additional damage points!
Elf(creature 1) has fainted! Match Over!

The battle begins: Elf[50,-34] vs Human[20,20]
Elf attacks for 23 points!
Human attacks for 13 points!
Tie Match! Both creatures have fainted

The battle begins: Elf[50,-47] vs Cyberdemon[20,30]
Elf attacks for 41 points!
Magical attack inflicts 41 additional damage points!
Cyberdemon attacks for 2 points!
Demonic attack inflicts 50 additional damage points!
Tie Match! Both creatures have fainted

The battle begins: Balrog[50,50] vs Human[20,20]
Balrog attacks for 3 points!
Balrog speed attack inflicts 7 additional damage points!
Human attacks for 8 points!
Balrog attacks for 16 points!
Balrog speed attack inflicts 46 additional damage points!
Human attacks for 9 points!
Human(creature 2) has fainted! Match Over!

The battle begins: Balrog[50,33] vs Cyberdemon[20,30]
Balrog attacks for 7 points!
Balrog speed attack inflicts 3 additional damage points!
Cyberdemon attacks for 6 points!
Demonic attack inflicts 50 additional damage points!
Balrog(creature 1) has fainted! Match Over!

The battle begins: Human[20,20] vs Cyberdemon[20,30]
Human attacks for 11 points!
Cyberdemon attacks for 2 points!
Human attacks for 16 points!
Cyberdemon attacks for 13 points!
Demonic attack inflicts 50 additional damage points!
Human(creature 1) has fainted! Match Over!

Nicole-Pav:A7 nicolepavlovich$ 
*/