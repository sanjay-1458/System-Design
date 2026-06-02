#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "PieceType.h"

class Knight : public Piece {

public:

    Knight(Color color, Position position);

    bool canMove(Position destination, const Board& board) override;

    std::vector<Position> getValidMoves(const Board& board) override;
    
    Piece* clone() const override;

    Color getColor() override;

    PieceType getType() override;
};

#endif