#include "ChessMoveCommand.h"

void ChessMoveCommand::execute() {

    board -> movePiece(move.getSource(), move.getDestination());
}

void ChessMoveCommand::undo() {

    board -> movePiece(move.getDestination(), move.getSource());
}

void ChessMoveCommand::setBoard(Board* board) {

    this -> board = board;
}

void ChessMoveCommand::setMove(Move move) {

    this -> move = move;
}