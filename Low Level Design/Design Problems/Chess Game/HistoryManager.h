#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <vector>
#include <stack>

#include "Move.h"

class HistoryManager {

private:

    std::vector<Move> moveHistory;

    std::stack<Move> undoStack;

    std::stack<Move> redoStack;

public:

    void recordMove(Move move);


    Move undo();

    Move redo();

    std::vector<Move> getHistory();
};

#endif