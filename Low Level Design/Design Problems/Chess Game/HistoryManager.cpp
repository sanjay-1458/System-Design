#include "HistoryManager.h"

void HistoryManager::recordMove(Move move) {

    moveHistory.push_back(move);

    undoStack.push(move);

    while(!redoStack.empty()) {

        redoStack.pop();
    }
}

Move HistoryManager::undo() {

    if(undoStack.empty()) {

        return Move();
    }

    Move move = undoStack.top();

    undoStack.pop();

    redoStack.push(move);

    return move;
}

Move HistoryManager::redo() {

    if(redoStack.empty()) {

        return Move();
    }

    Move move = redoStack.top();

    redoStack.pop();

    undoStack.push(move);

    return move;
}

std::vector<Move> HistoryManager::getHistory() {

    return moveHistory;
}

