#include <iostream>

#include "ChessGame.h"
#include "BroadcastSpectator.h"
#include "PenguinSpectator.h"
#include "Move.h"

int main() {

    Player white("P1", "Player-A", Color::WHITE);
    Player black("P2", "Player-B", Color::BLACK);

    ChessGame game(white, black);

    BroadcastSpectator broadcast("S1", "Broadcast");
    PenguinSpectator penguin("S2", "Penguin");

    game.addSpectator(&broadcast);
    game.addSpectator(&penguin);

    game.startGame();

    Move move1 = MoveBuilder()
        .setMoveNumber(1)
        .setSource(Position(6, 4))
        .setDestination(Position(5, 4))
        .setMovedPieceType(PieceType::PAWN)
        .setPlayerId("P1")
        .build();
    game.makeMove(move1);

    Move move2 = MoveBuilder()
        .setMoveNumber(2)
        .setSource(Position(1, 4))
        .setDestination(Position(2, 4))
        .setMovedPieceType(PieceType::PAWN)
        .setPlayerId("P2")
        .build();
    game.makeMove(move2);

    Move move3 = MoveBuilder()
        .setMoveNumber(3)
        .setSource(Position(7, 6))
        .setDestination(Position(5, 5))
        .setMovedPieceType(PieceType::KNIGHT)
        .setPlayerId("P1")
        .build();
    game.makeMove(move3);

    Move move4 = MoveBuilder()
        .setMoveNumber(4)
        .setSource(Position(0, 1))
        .setDestination(Position(2, 2))
        .setMovedPieceType(PieceType::KNIGHT)
        .setPlayerId("P2")
        .build();
    game.makeMove(move4);

    Move move5 = MoveBuilder()
        .setMoveNumber(5)
        .setSource(Position(7, 5))
        .setDestination(Position(6, 4))
        .setMovedPieceType(PieceType::BISHOP)
        .setPlayerId("P1")
        .build();
    game.makeMove(move5);

    Move move6 = MoveBuilder()
        .setMoveNumber(6)
        .setSource(Position(0, 6))
        .setDestination(Position(2, 5))
        .setMovedPieceType(PieceType::KNIGHT)
        .setPlayerId("P2")
        .build();
    game.makeMove(move6);

    std::cout << "History: " << std::endl;
    game.showHistory();

    std::cout << "Undo: " << std::endl;
    game.undoMove();

    std::cout << "Redo: " << std::endl;
    game.redoMove();

    std::cout << "Save: " << std::endl;
    game.saveGame();

    std::cout << "Resign: " << std::endl;
    game.resign(black);

    return 0;
}