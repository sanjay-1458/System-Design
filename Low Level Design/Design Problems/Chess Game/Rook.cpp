#include "Rook.h"
#include "Board.h"

Rook::Rook(Color color, Position position) {

    this -> color = color;

    this -> position = position;
}

bool Rook::canMove(Position destination, const Board& board) {

    return (position.row == destination.row || position.column == destination.column);
}

std::vector<Position> Rook::getValidMoves(const Board& board) {

    return {};
}

Piece* Rook::clone() const {

    return new Rook(*this);
}

Color Rook::getColor() {

    return color;
}

PieceType Rook::getType() {

    return PieceType::ROOK;
}