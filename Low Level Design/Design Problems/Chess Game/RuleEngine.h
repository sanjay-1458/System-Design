#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include "Board.h"
#include "Player.h"
#include "Color.h"

class RuleEngine {

private:

    bool hasLegalMove(const Board& board, Color color);

public:

    bool isCheck(const Board& board, Color color);

    bool isCheckmate(const Board& board, Color color);

    bool isStalemate(const Board& board, Color color);

    bool isDraw(const Board& board);

    bool isValidCastling(const Board& board, Move move);

    Player determineWinner(const Player& whitePlayer, const Player& blackPlayer, const Board& board);

};

#endif