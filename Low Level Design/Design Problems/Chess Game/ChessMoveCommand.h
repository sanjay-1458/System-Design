#ifndef CHESS_MOVE_COMMAND_H
#define CHESS_MOVE_COMMAND_H

#include "MoveCommand.h"
#include "Board.h"
#include "Move.h"

class ChessMoveCommand : public MoveCommand {

private:

    Board* board;

    Move move;

public:

    void execute() override;

    void undo() override;

    void setBoard(Board* board);

    void setMove(Move move);
};

#endif