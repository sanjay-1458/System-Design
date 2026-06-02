#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "Move.h"
#include "Board.h"
#include "Player.h"
#include "RuleEngine.h"

class MoveValidator {

    RuleEngine* ruleEngine;

public:

    MoveValidator(RuleEngine* ruleEngine) {
        
        this -> ruleEngine = ruleEngine;
    }

    bool isValidMove(Move move, const Board& board, Player currentPlayer);

    bool validatePieceMovement(Move move, const Board& board);

    bool validateCastling(Move move, const Board& board);

    bool validatePromotion(Move move, const Board& board);

    bool validateKingSafety(Move move, const Board& board);

};

#endif

