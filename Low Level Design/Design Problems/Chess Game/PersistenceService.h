#ifndef PERSISTENCE_SERVICE_H
#define PERSISTENCE_SERVICE_H

#include <string>

class ChessGame;

class PersistenceService {

public:

    void saveGame(const ChessGame& game);

    void loadGame(std::string gameId, ChessGame& game);
};

#endif