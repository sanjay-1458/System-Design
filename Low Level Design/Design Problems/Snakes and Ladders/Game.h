#ifndef GAME_H
#define GAME_H

#include "Dice.h"
#include "Board.h"
#include "Player.h"



class Game {

    Dice* dice;
    Board* board;
    vector<Player*> players;

    int currentPlayerIndex;

    
    public:
    
    Game(Dice* dice, Board* board);

    void addPlayer(Player* player);
    
    void startGame();
    void playTurn();
    bool gameOver();
    int findNextPlayer();
};

#endif