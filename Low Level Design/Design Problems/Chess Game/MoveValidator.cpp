#include <cmath>

#include "MoveValidator.h"
#include "Piece.h"

#include<iostream>

bool MoveValidator::isValidMove(Move move, const Board& board, Player currentPlayer) {

    // Here validation is not a giant function, its a step wise multi layer validation

    // 1. Source square must not be empty

    if(board.isEmpty(move.getSource())) {

        return false;
    }

    Piece* piece = board.getPiece(move.getSource());

    // 2. Current Player must own the piece

    if(piece -> getColor() != currentPlayer.getColor()) {

        return false;
    }

    // 3. Destination must be inside the board

    Position destination = move.getDestination();

    if(!(destination.row >= 0 && destination.row < 8 && destination.column >= 0 && destination.column < 8)) {

        return false;
    }

    // 4. Destination piece should not be owned by current player

    Piece* destinationPiece = board.getPiece(destination);

    if(destinationPiece != nullptr && destinationPiece->getColor() == currentPlayer.getColor()) {

        return false;
    }

    // 5. Can current piece move to that destination?

    if(!validatePieceMovement(move, board)) {

        return false;
    }

    // 6. Are we doing Castling?

    if(!validateCastling(move, board)) {

        return false;
    }

    // 7. Are we doing promotion?

    if(!validatePromotion(move, board)) {

        return false;
    }

    // 8. Is king safe after move?

    if(!validateKingSafety(move, board)) {

        return false;
    }

    return true;
}

bool MoveValidator::validatePieceMovement(Move move, const Board& board) {

    Piece* piece = board.getPiece(move.getSource());

    return piece -> canMove(move.getDestination(), board);
}

bool MoveValidator::validateCastling(Move move, const Board& board) {

    Piece* piece = board.getPiece(move.getSource());

    // Only king can castle

    if(piece -> getType() != PieceType::KING) {

        return true;
    }

    int columnDifference = std::abs(move.getDestination().column - move.getSource().column);

    if(columnDifference != 2) {

        return true;
    }

    if(!move.isCastlingMove()) {

        return false;
    }

        // Castling attempt

    return ruleEngine->isValidCastling(board, move);
}

bool MoveValidator::validatePromotion(Move move, const Board& board) {

    Piece* piece = board.getPiece(move.getSource());

    if(piece -> getType() != PieceType::PAWN) {

        return true;
    }

    Position destination = move.getDestination();

    bool reachedLastRank =(piece -> getColor() == Color::WHITE && destination.row == 0) || (piece -> getColor() == Color::BLACK && destination.row == 7);

    if(!reachedLastRank) {

        return true;
    }

    if(!move.isPromotionMove()) {

        return false;
    }

    // Cannot promote to king

    if(move.getPromotedPieceType() == PieceType::KING) {

        return false;
    }

    return true;
}

bool MoveValidator::validateKingSafety(Move move, const Board& board) {

    Piece* piece = board.getPiece(move.getSource());

    Board temp;

    temp.restoreBoard(board);

    temp.movePiece(move.getSource(), move.getDestination());

    if(ruleEngine -> isCheck(temp, piece -> getColor())) {

        return false;
    }

    return true;
}