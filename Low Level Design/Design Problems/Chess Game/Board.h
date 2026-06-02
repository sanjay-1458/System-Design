#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Color.h"
#include "Position.h"

class Piece;

class Board {

private:

    Piece* squares[8][8];

public:

    Board();

    void initializeBoard();

    void placePiece(Piece* piece, Position position);

    void movePiece(Position source, Position destination);

    void removePiece(Position position);

    Piece* getPiece(Position position) const;

    bool isOccupied(Position position) const;

    bool isEmpty(Position position) const;

    Position findKing(Color color) const;

    std::vector<Piece*> getAllPieces(Color color) const;

    void printBoard();

    void restoreBoard(const Board& boardState);

    ~Board();
};

#endif