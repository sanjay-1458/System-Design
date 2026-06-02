#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "PieceType.h"

class Queen : public Piece {

public:

    Queen(Color color, Position position);

    bool canMove(Position destination, const Board& board) override;

    std::vector<Position> getValidMoves(const Board& board) override;
    
    Piece* clone() const override;

    Color getColor() override;

    PieceType getType() override;
};

#endif