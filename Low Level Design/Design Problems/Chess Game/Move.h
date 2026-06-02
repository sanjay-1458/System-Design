#ifndef MOVE_H
#define MOVE_H

#include <string>

#include "Position.h"
#include "PieceType.h"

class Move {

private:

    int moveNumber;

    Position source;

    Position destination;

    PieceType movedPieceType;

    PieceType capturedPieceType;

    PieceType promotedPieceType;

    std::string playerId;

    bool castlingMove;

    bool promotionMove;

    Move(int moveNumber, Position source, Position destination, PieceType movedPieceType, PieceType capturedPieceType, PieceType promotedPieceType, std::string playerId, bool castlingMove, bool promotionMove);

public:

    Position getSource() const;

    Position getDestination() const;

    PieceType getMovedPieceType() const;

    PieceType getCapturedPieceType() const;

    PieceType getPromotedPieceType() const;

    std::string getPlayerId() const;

    bool isCastlingMove() const;

    int getMoveNumber() const;

    bool isPromotionMove() const;

    friend class MoveBuilder;

    Move();
};

class MoveBuilder {

private:

    int moveNumber = 0;

    Position source = Position(0, 0);

    Position destination = Position(0, 0);

    PieceType movedPieceType = PieceType::PAWN;

    PieceType capturedPieceType = PieceType::PAWN;

    PieceType promotedPieceType = PieceType::PAWN;

    std::string playerId = "";

    bool castlingMove = false;

    bool promotionMove = false;

public:

    MoveBuilder& setMoveNumber(int moveNumber);

    MoveBuilder& setSource(Position source);

    MoveBuilder& setDestination(Position destination);

    MoveBuilder& setMovedPieceType(PieceType movedPieceType);

    MoveBuilder& setCapturedPieceType(PieceType capturedPieceType);

    MoveBuilder& setPromotedPieceType(PieceType promotedPieceType);

    MoveBuilder& setPlayerId(std::string playerId);

    MoveBuilder& setCastlingMove(bool castlingMove);

    MoveBuilder& setPromotionMove(bool promotionMove);

    Move build();
};

#endif