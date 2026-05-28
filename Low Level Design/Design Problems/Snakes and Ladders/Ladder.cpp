#include "Ladder.h"

Ladder::Ladder(int start, int end) {

    this -> start = start;
    this -> end = end;
}

int Ladder::getStart() const {

    return start;
}
int Ladder::getEnd() const {

    return end;
}