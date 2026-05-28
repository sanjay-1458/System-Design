#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {

private:

    std::string name;
    int position;

    bool won;

public:

    Player(std::string name);

    void setPos(int pos);

    int getPosition() const;

    std::string getName() const;

    bool isWinner() const;

    void setWinner();
};

#endif