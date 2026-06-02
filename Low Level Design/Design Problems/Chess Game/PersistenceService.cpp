
#include "ChessGame.h"
#include "PersistenceService.h"

#include <iostream>

void PersistenceService::saveGame(const ChessGame& game) {

    std::cout << "Saving game..." << std::endl;
}

void PersistenceService::loadGame(std::string gameId, ChessGame& game) {

    std::cout << "Loading game: " << gameId << std::endl;
}