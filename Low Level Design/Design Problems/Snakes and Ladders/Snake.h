#ifndef SNAKE_H
#define SNAKE_H

class Snake {

    int head, tail;

public:

    Snake(int head, int tail);

    int getHead() const;
    int getTail() const;
};

#endif