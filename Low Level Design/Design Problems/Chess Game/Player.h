#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Color.h"
#include "Move.h"
#include "Position.h"

class Player {

private:

    std::string id;

    std::string name;

    Color color;

public:

    Player(std::string id, std::string name, Color color);

    std::string getId() const;

    std::string getName() const;

    Color getColor() const;

    Move requestMove(Position source, Position destination);
};

#endif