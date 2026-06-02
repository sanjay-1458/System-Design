#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "Board.h"
#include "Player.h"
#include "GameStatus.h"
#include "MoveValidator.h"
#include "RuleEngine.h"
#include "HistoryManager.h"
#include "NotificationService.h"
#include "PersistenceService.h"
#include "Spectator.h"

class ChessGame {

private:

    Board board;

    Player whitePlayer;

    Player blackPlayer;

    Player* currentPlayer;

    GameStatus status;

    RuleEngine ruleEngine;

    MoveValidator moveValidator;

    HistoryManager historyManager;

    NotificationService notificationService;

    PersistenceService persistenceService;

public:

    ChessGame(Player whitePlayer, Player blackPlayer);

    void startGame();

    void makeMove(Move move);

    void resign(Player player);

    void saveGame();

    void addSpectator(Spectator* spectator);

    void removeSpectator(Spectator* spectator);

    void switchTurn();

    void undoMove();

    void redoMove();

    void showHistory();
};

#endif