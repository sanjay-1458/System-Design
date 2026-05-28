#include "Board.h"

Board::Board(int size) {

    this -> size = size;
}

void Board::addSnake(Snake* snake) {

    snakes.push_back(snake);
    snakeMovement[snake -> getHead()] = snake -> getTail();
}

void Board::addLadder(Ladder* ladder) {

    ladders.push_back(ladder);
    ladderMovement[ladder -> getStart()] = ladder -> getEnd();
}

bool Board::isLadder(int cell) {

    return (ladderMovement.find(cell) != ladderMovement.end());
}

bool Board::isSnake(int cell) {

    return (snakeMovement.find(cell) != snakeMovement.end());
}

int Board::jumpSnake(int cell) {

    return snakeMovement[cell];
}

int Board::jumpLadder(int cell) {

    return ladderMovement[cell];
}

bool Board::isWithinBoard(int pos) {

    return (pos >= 1 && pos <= size * size);
}

int Board::getLastCell() {

    return size * size;
}