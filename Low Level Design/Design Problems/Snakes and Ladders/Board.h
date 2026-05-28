#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Ladder.h"
#include <vector>
#include <map>

using std::vector;
using std::map;


class Board {

    vector<Snake*> snakes;
    vector<Ladder*> ladders;

    int size;

    map<int, int> snakeMovement;
    map<int, int> ladderMovement;
    
public:
    

    Board(int size);
    
    void addSnake(Snake* snake);

    void addLadder(Ladder* ladder);

    bool isLadder(int cell);

    bool isSnake(int cell);

    int jumpSnake(int cell);

    int jumpLadder(int cell);

    bool isWithinBoard(int pos);

    int getLastCell();
};

#endif