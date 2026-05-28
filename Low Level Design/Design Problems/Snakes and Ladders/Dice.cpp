#include "Dice.h"
#include <cstdlib>

int Dice::diceRoll() {

    return rand() % 6 + 1;    
}
