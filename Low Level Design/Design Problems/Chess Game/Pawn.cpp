#include <cmath>

#include "Board.h"
#include "Pawn.h"

Pawn::Pawn(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}


bool Pawn::canMove(Position destination, const Board& board) {

    int direction = (color == Color::WHITE ? -1 : 1);

    int rowDiff = destination.row - position.row;

    int colDiff = std::abs(destination.column - position.column);

    Piece* destinationPiece = board.getPiece(destination);

    if(colDiff == 0 && rowDiff == direction && destinationPiece == nullptr) {

        return true;
    }

    if(!hasMoved && colDiff == 0 && rowDiff == 2 * direction && destinationPiece == nullptr) {

        return true;
    }

    if(colDiff == 1 && rowDiff == direction && destinationPiece != nullptr && destinationPiece->getColor() != color) {

        return true;
    }

    return false;
}


std::vector<Position> Pawn::getValidMoves(const Board& board) {

    return {};
}

Piece* Pawn::clone() const {

    return new Pawn(*this);
}

Color Pawn::getColor() {

    return color;
}

PieceType Pawn::getType() {

    return PieceType::PAWN;
}