#include "Player.h"

Player::Player(std::string name) {

    this -> name = name;
    this -> position = 1;
    this -> won = false;
}

void Player::setPos(int pos) {

    this -> position = pos;
}

int Player::getPosition() const {

    return this -> position;
}

std::string Player::getName() const {

    return this -> name;
}

bool Player::isWinner() const {

    return this -> won;
}

void Player::setWinner() {

    won = true;
}