#include <cmath>

#include "Queen.h"
#include "Board.h"

Queen::Queen(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}

bool Queen::canMove(Position destination, const Board& board) {

    int rowDiff = std::abs(destination.row - position.row);

    int colDiff = std::abs(destination.column - position.column);

    return rowDiff == (colDiff || rowDiff == 0 || colDiff == 0);
}

std::vector<Position> Queen::getValidMoves(const Board& board) {

    return {};
}

Piece* Queen::clone() const {

    return new Queen(*this);
}

Color Queen::getColor() {

    return color;
}

PieceType Queen::getType() {

    return PieceType::QUEEN;
}