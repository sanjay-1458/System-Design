#include "Board.h"
#include "PieceType.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"

#include <iostream>


Board::Board() {

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            squares[row][col] = nullptr;
        }
    }
}

void Board::initializeBoard() {

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            squares[row][col] = nullptr;
        }
    }

    // Black Pieces

    squares[0][0] = new Rook(Color::BLACK, Position(0, 0));
    squares[0][1] = new Knight(Color::BLACK, Position(0, 1));
    squares[0][2] = new Bishop(Color::BLACK, Position(0, 2));
    squares[0][3] = new Queen(Color::BLACK, Position(0, 3));
    squares[0][4] = new King(Color::BLACK, Position(0, 4));
    squares[0][5] = new Bishop(Color::BLACK, Position(0, 5));
    squares[0][6] = new Knight(Color::BLACK, Position(0, 6));
    squares[0][7] = new Rook(Color::BLACK, Position(0, 7));

    
    for(int col = 0; col < 8; ++col) {

        squares[1][col] = new Pawn(Color::BLACK, Position(1, col));
    }

    // White Pieces
    
    for(int col = 0; col < 8; ++col) {

        squares[6][col] = new Pawn(Color::WHITE, Position(6, col));
    }


    squares[7][0] = new Rook(Color::WHITE, Position(7, 0));
    squares[7][1] = new Knight(Color::WHITE, Position(7, 1));
    squares[7][2] = new Bishop(Color::WHITE, Position(7, 2));
    squares[7][3] = new Queen(Color::WHITE, Position(7, 3));
    squares[7][4] = new King(Color::WHITE, Position(7, 4));
    squares[7][5] = new Bishop(Color::WHITE, Position(7, 5));
    squares[7][6] = new Knight(Color::WHITE, Position(7, 6));
    squares[7][7] = new Rook(Color::WHITE, Position(7, 7));
}

void Board::placePiece(Piece* piece, Position position) {

    squares[position.row][position.column] = piece;
}

void Board::movePiece(Position source, Position destination) {

    Piece* piece = squares[source.row][source.column];

    if(piece == nullptr) {

        return;
    }

    squares[destination.row][destination.column] = piece;

    squares[source.row][source.column] = nullptr;

    piece -> setPosition(destination);

    piece -> setHasMoved(true);
}

void Board::removePiece(Position position) {

    squares[position.row][position.column] = nullptr;
}

Piece* Board::getPiece(Position position) const {


    return squares[position.row][position.column];
}
bool Board::isOccupied(Position position) const{

    return (squares[position.row][position.column] != nullptr);
}

bool Board::isEmpty(Position position) const{

    return !isOccupied(position);
}

void Board::restoreBoard(const Board& boardState) {

    for(int i = 0; i < 8; ++i) {

        for(int j = 0; j < 8; ++j) {

            delete squares[i][j];

            squares[i][j] = nullptr;
            
            Piece* piece = boardState.getPiece(Position(i, j));

            if(piece != nullptr) {

                squares[i][j] = piece -> clone();
            }
        }
    }
}

Position Board::findKing(Color color) const{

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            Piece* piece = squares[row][col];

            if(piece != nullptr && piece->getColor() == color && piece->getType() == PieceType::KING) {

                return Position(row, col);
            }
        }
    }

    return Position(-1, -1);
}

std::vector<Piece*> Board::getAllPieces(Color color) const{

    std::vector<Piece*> pieces;

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            Piece* piece = squares[row][col];

            if(piece != nullptr && piece -> getColor() == color) {

                pieces.push_back(piece);
            }
        }
    }

    return pieces;
}


void Board::printBoard() {

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            Piece* piece = squares[row][col];

            if(piece == nullptr) {

                std::cout << ". ";
            }
            else if(piece -> getType() == PieceType::KING) {

                std::cout << "K ";
            }
            else if(piece -> getType() == PieceType::QUEEN) {

                std::cout << "Q ";
            }
            else if(piece -> getType() == PieceType::ROOK) {

                std::cout << "R ";
            }
            else if(piece -> getType() == PieceType::BISHOP) {

                std::cout << "B ";
            }
            else if(piece -> getType() == PieceType::KNIGHT) {

                std::cout << "N ";
            }
            else {

                std::cout << "P ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}


Board::~Board() {

    for(int row = 0; row < 8; ++row) {

        for(int col = 0; col < 8; ++col) {

            delete squares[row][col];
        }
    }
}