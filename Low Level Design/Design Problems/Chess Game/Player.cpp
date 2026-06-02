#include "Player.h"

Player::Player(std::string id, std::string name, Color color) {

    this -> id = id;

    this -> name = name;

    this -> color = color;
}

std::string Player::getId() const {

    return id;
}

std::string Player::getName() const {

    return name;
}

Color Player::getColor() const {

    return color;
}

Move Player::requestMove(Position source, Position destination) {

    return MoveBuilder()
        .setSource(source)
        .setDestination(destination)
        .setPlayerId(id)
        .build();
}