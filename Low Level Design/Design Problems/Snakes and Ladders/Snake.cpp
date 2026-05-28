#include "Snake.h"

Snake::Snake(int head, int tail) {

    this -> head = head;
    this -> tail = tail;
}

int Snake::getHead() const {

    return head;
}
int Snake::getTail() const {

    return tail;
}