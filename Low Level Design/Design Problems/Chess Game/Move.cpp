#include "Move.h"

Move::Move(int moveNumber, Position source, Position destination, PieceType movedPieceType, PieceType capturedPieceType, PieceType promotedPieceType, std::string playerId, bool castlingMove, bool promotionMove) {

    this -> moveNumber = moveNumber;

    this -> source = source;

    this -> destination = destination;

    this -> movedPieceType = movedPieceType;

    this -> capturedPieceType = capturedPieceType;

    this -> promotedPieceType = promotedPieceType;

    this -> playerId = playerId;

    this -> castlingMove = castlingMove;

    this -> promotionMove = promotionMove;
}

Move::Move()
    : moveNumber(0),
      source(0, 0),
      destination(0, 0),
      movedPieceType(PieceType::PAWN),
      capturedPieceType(PieceType::PAWN),
      promotedPieceType(PieceType::PAWN),
      playerId(""),
      castlingMove(false),
      promotionMove(false) {
}

int Move::getMoveNumber() const {

    return moveNumber;
}

Position Move::getSource() const {

    return source;
}

Position Move::getDestination() const {

    return destination;
}

PieceType Move::getMovedPieceType() const {

    return movedPieceType;
}

PieceType Move::getCapturedPieceType() const {

    return capturedPieceType;
}

PieceType Move::getPromotedPieceType() const {

    return promotedPieceType;
}

std::string Move::getPlayerId() const {

    return playerId;
}

bool Move::isCastlingMove() const {

    return castlingMove;
}

bool Move::isPromotionMove() const {

    return promotionMove;
}

MoveBuilder& MoveBuilder::setMoveNumber(int moveNumber) {

    this -> moveNumber = moveNumber;

    return *this;
}

MoveBuilder& MoveBuilder::setSource(Position source) {

    this -> source = source;

    return *this;
}

MoveBuilder& MoveBuilder::setDestination(Position destination) {

    this -> destination = destination;

    return *this;
}

MoveBuilder& MoveBuilder::setMovedPieceType(PieceType movedPieceType) {

    this -> movedPieceType = movedPieceType;

    return *this;
}

MoveBuilder& MoveBuilder::setCapturedPieceType(PieceType capturedPieceType) {

    this -> capturedPieceType = capturedPieceType;

    return *this;
}

MoveBuilder& MoveBuilder::setPromotedPieceType(PieceType promotedPieceType) {

    this -> promotedPieceType = promotedPieceType;

    return *this;
}

MoveBuilder& MoveBuilder::setPlayerId(std::string playerId) {

    this -> playerId = playerId;

    return *this;
}

MoveBuilder& MoveBuilder::setCastlingMove(bool castlingMove) {

    this -> castlingMove = castlingMove;

    return *this;
}

MoveBuilder& MoveBuilder::setPromotionMove(bool promotionMove) {

    this -> promotionMove = promotionMove;

    return *this;
}

Move MoveBuilder::build() {

    return Move(
        moveNumber,
        source,
        destination,
        movedPieceType,
        capturedPieceType,
        promotedPieceType,
        playerId,
        castlingMove,
        promotionMove
    );
}