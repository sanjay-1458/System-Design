#include <iostream>
#include "Game.h"


using std::cout;
using std::endl;

Game::Game(Dice* dice, Board* board) {

    this -> dice = dice;
    this -> board = board;
    this -> currentPlayerIndex = 0;
    
}

void Game::playTurn() {

    int steps = dice -> diceRoll();

    int nextPos = players[currentPlayerIndex] -> getPosition() + steps;

    if(board -> isWithinBoard(nextPos)) {

        if(board -> isSnake(nextPos)) {

            nextPos = board -> jumpSnake(nextPos);
        }
        else if(board -> isLadder(nextPos)) {

            nextPos = board -> jumpLadder(nextPos);
        }

        players[currentPlayerIndex] -> setPos(nextPos);

        if(nextPos == board -> getLastCell()) {

            players[currentPlayerIndex] -> setWinner();
        }
    
        if(steps == 6 && players[currentPlayerIndex] -> isWinner() == false) {

            playTurn();
        }
    }
}

void Game::startGame() {

    while(!gameOver()) {

        playTurn();

        if(players[currentPlayerIndex] -> isWinner()) {

            cout << "Player: " << players[currentPlayerIndex] -> getName() << " winned the game " << endl;
        }

        if(!gameOver()) {


            currentPlayerIndex = findNextPlayer();
        }
        else {

            cout << "Game has ended. Players who winned are:  " << endl;

            for(auto player : players) {

                if(player -> isWinner()) {

                    cout << player -> getName() << endl;
                }
            }
            break;
        }
    }
}

bool Game::gameOver() {

    int cnt = 0;

    for(auto player : players) {

        if(player -> isWinner()) {

            cnt++;
        }
    }

    return (cnt == (int)players.size() - 1);
}


int Game::findNextPlayer() {

    int nextPlayer = (currentPlayerIndex + 1) % (int)players.size();

    while(players[nextPlayer] -> isWinner()) {

        nextPlayer = (nextPlayer + 1) % (int)players.size();
    }

    return nextPlayer;
}


void Game::addPlayer(Player* player) {

    players.push_back(player);
}