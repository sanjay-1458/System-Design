#include <cmath>
#include "Board.h"

#include "Knight.h"

Knight::Knight(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}

bool Knight::canMove(Position destination, const Board& board) {

    int rowDiff = std::abs(destination.row - position.row);

    int colDiff = std::abs(destination.column - position.column);

    return ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2));
}

std::vector<Position> Knight::getValidMoves(const Board& board) {

    return {};
}

Piece* Knight::clone() const {

    return new Knight(*this);
}

Color Knight::getColor() {

    return color;
}

PieceType Knight::getType() {

    return PieceType::KNIGHT;
}