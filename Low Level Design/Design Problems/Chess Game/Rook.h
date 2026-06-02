#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "PieceType.h"

class Rook : public Piece {

public:

    Rook(Color color, Position position);

    bool canMove(Position destination, const Board& board) override;

    std::vector<Position> getValidMoves(const Board& board) override;

    Piece* clone() const override;

    Color getColor() override;

    PieceType getType() override;
};

#endif