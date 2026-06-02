#include "ChessGame.h"
#include "ChessMoveCommand.h"

#include <iostream>

ChessGame::ChessGame(Player whitePlayer, Player blackPlayer):whitePlayer(whitePlayer), blackPlayer(blackPlayer), moveValidator(&ruleEngine) {

    currentPlayer = &this -> whitePlayer;

    status = GameStatus::IN_PROGRESS;
}

void ChessGame::startGame() {

    board.initializeBoard();

    currentPlayer = &whitePlayer;

    status = GameStatus::IN_PROGRESS;

    board.printBoard();

    notificationService.notifyObservers("Game Started");
}

void ChessGame::makeMove(Move move) {

    if(!moveValidator.isValidMove(move, board, *currentPlayer)) {

        return;
    }

    board.movePiece(move.getSource(), move.getDestination());

    board.printBoard();

    historyManager.recordMove(move);

    notificationService.notifyObservers("Move Played");

    Color opponentColor = (currentPlayer -> getColor() == Color::WHITE ? Color::BLACK : Color::WHITE);

    if(ruleEngine.isCheckmate(board, opponentColor)) {

        status = GameStatus::CHECKMATE;

        notificationService.notifyObservers("Checkmate");

        return;
    }

    if(ruleEngine.isStalemate(board, opponentColor)) {

        status = GameStatus::STALEMATE;

        notificationService.notifyObservers("Stalemate");

        return;
    }

    if(ruleEngine.isCheck(board, opponentColor)) {

        status = GameStatus::CHECK;

        notificationService.notifyObservers("Check");
    }

    switchTurn();
}

void ChessGame::switchTurn() {

    if(currentPlayer == &whitePlayer) {

        currentPlayer = &blackPlayer;
    }
    else {

        currentPlayer = &whitePlayer;
    }
}

void ChessGame::resign(Player player) {

    status = GameStatus::RESIGNED;

    notificationService.notifyObservers(player.getName() + " resigned");
}

void ChessGame::saveGame() {

    persistenceService.saveGame(*this);
}


void ChessGame::addSpectator(Spectator* spectator) {

    notificationService.addObserver(spectator);
}

void ChessGame::removeSpectator(Spectator* spectator) {

    notificationService.removeObserver(spectator);
}

void ChessGame::undoMove() {

    Move move = historyManager.undo();

    if(move.getMoveNumber() == 0) {

        return;
    }

    ChessMoveCommand command;

    command.setBoard(&board);

    command.setMove(move);

    command.undo();

    board.printBoard();

    notificationService.notifyObservers("Undo Performed");

    switchTurn();
}


void ChessGame::redoMove() {

    Move move = historyManager.redo();

    if(move.getMoveNumber() == 0) {

        return;
    }

    ChessMoveCommand command;

    command.setBoard(&board);

    command.setMove(move);

    command.execute();

    board.printBoard();

    notificationService.notifyObservers("Redo Performed");

    switchTurn();
}



void ChessGame::showHistory() {

    std::vector<Move> moves = historyManager.getHistory();

    for(Move move : moves) {

        std::cout << "Move " << move.getMoveNumber() << " : (" << move.getSource().row << "," << move.getSource().column << ") -> (" << move.getDestination().row << "," << move.getDestination().column << ")" << std::endl;
    }
}