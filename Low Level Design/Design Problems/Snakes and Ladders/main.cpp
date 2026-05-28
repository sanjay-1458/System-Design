#include <iostream>

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "Snake.h"
#include "Ladder.h"


int main() {

    Dice* dice = new Dice();
    Snake* snake = new Snake(44, 22);
    Ladder* ladder = new Ladder(23, 98);
    Board* board = new Board(10);

    Player* playerA = new Player("Cat-1");
    Player* playerB = new Player("Cat-2");

    board -> addLadder(ladder);
    board -> addSnake(snake);

    Game* game = new Game(dice, board);

    game -> addPlayer(playerA);
    game -> addPlayer(playerB);

    game -> startGame();
    
    delete dice;
    delete snake;
    delete ladder;
    delete game;
    delete playerA;
    delete playerB;
    delete board;

    return 0;
}
