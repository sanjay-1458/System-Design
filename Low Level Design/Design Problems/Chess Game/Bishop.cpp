#include <cmath>

#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}

bool Bishop::canMove(Position destination, const Board& board) {

    int rowDiff = std::abs(destination.row - position.row);

    int colDiff = std::abs(destination.column - position.column);

    return rowDiff == colDiff;
}

std::vector<Position> Bishop::getValidMoves(const Board& board) {

    return {};
}

Piece* Bishop::clone() const {

    return new Bishop(*this);
}

Color Bishop::getColor() {

    return color;
}

PieceType Bishop::getType() {

    return PieceType::BISHOP;
}