#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "PieceType.h"

class Bishop : public Piece {

public:

    Bishop(Color color, Position position);

    bool canMove(Position destination, const Board& board) override;

    std::vector<Position> getValidMoves(const Board& board) override;
    
    Piece* clone() const override;

    Color getColor() override;

    PieceType getType() override;
};

#endif