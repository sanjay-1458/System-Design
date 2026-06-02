#include "RuleEngine.h"
#include "Piece.h"

bool RuleEngine::isCheck(const Board& board, Color color) {

    Position kingPosition = board.findKing(color);

    Color opponentColor = (color == Color::WHITE ? Color::BLACK : Color::WHITE);

    std::vector<Piece*> opponentPieces = board.getAllPieces(opponentColor);

    for(Piece* piece : opponentPieces) {

        if(piece -> canMove(kingPosition, board)) {

            return true;
        }
    }

    return false;
}

bool RuleEngine::isCheckmate(const Board& board, Color color) {

    if(!isCheck(board, color)) {

        return false;
    }

    if(hasLegalMove(board, color)) {

        return false;
    }

    return true;
}

bool RuleEngine::isStalemate(const Board& board, Color color) {

    if(isCheck(board, color)) {

        return false;
    }

    if(hasLegalMove(board, color)) {

        return false;
    }

    return true;
}

bool RuleEngine::isDraw(const Board& board) {

    return false;
}

Player RuleEngine::determineWinner(const Player& whitePlayer, const Player& blackPlayer, const Board& board) {

    if(isCheckmate(board, Color::WHITE)) {

        return blackPlayer;
    }

    if(isCheckmate(board, Color::BLACK)) {

        return whitePlayer;
    }

    return whitePlayer;
}

bool RuleEngine::isValidCastling(const Board& board, Move move) {

    Piece* king = board.getPiece(move.getSource());

    if(king == nullptr) {

        return false;
    }

    if(king -> getHasMoved()) {

        return false;
    }

    int row = move.getSource().row;

    bool kingSide = (move.getDestination().column > move.getSource().column);

    Position rookPosition = (kingSide ? Position(row, 7) : Position(row, 0));

    Piece* rook = board.getPiece(rookPosition);

    if(rook == nullptr) {

        return false;
    }

    if(rook -> getType() != PieceType::ROOK) {

        return false;
    }

    if(rook -> getHasMoved()) {

        return false;
    }

    int start = (kingSide ? move.getSource().column + 1 : 1);

    int end = (kingSide ? 6 : move.getSource().column - 1);

    for(int col = start; col <= end; ++col) {

        if(board.isOccupied(Position(row, col))) {

            return false;
        }
    }

    if(isCheck(board, king -> getColor())) {

        return false;
    }

    return true;
}

bool RuleEngine::hasLegalMove(const Board& board, Color color) {

    // std::vector<Piece*> pieces = board.getAllPieces(color);

    // for(Piece* piece : pieces) {

    //     std::vector<Position> moves = piece->getValidMoves(board);

    //     if(!moves.empty()) {

    //         return true;
    //     }
    // }

    return true;
}