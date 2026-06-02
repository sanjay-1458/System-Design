#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "Color.h"
#include "Position.h"
#include "PieceType.h"

class Board;

class Piece {

protected:

    Color color;

    Position position;

public:

    virtual bool canMove(Position destination, const Board& board) = 0;

    virtual std::vector<Position> getValidMoves(const Board& board) = 0;

    virtual Piece* clone() const = 0;

    virtual Color getColor() = 0;

    virtual PieceType getType() = 0;

    bool hasMoved = false;

    bool getHasMoved() {

        return hasMoved;
    }

    void setHasMoved(bool hasMoved) {

        this -> hasMoved = hasMoved;
    }

    Position getPosition() {

        return position;
    }

    void setPosition(Position position) {

        this -> position = position;
    }

    virtual ~Piece() = default;
};

#endif