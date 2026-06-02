#include "King.h"
#include "Board.h"

#include <cmath>

King::King(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}

bool King::canMove(Position destination, const Board& board) {

    int rowDiff = std::abs(destination.row - position.row);

    int colDiff = std::abs(destination.column - position.column);

    return (rowDiff <= 1 && colDiff <= 1);
}

std::vector<Position> King::getValidMoves(const Board& board) {

    return {};
}

Piece* King::clone() const {

    return new King(*this);
}

Color King::getColor() {

    return color;
}

PieceType King::getType() {

    return PieceType::KING;
}