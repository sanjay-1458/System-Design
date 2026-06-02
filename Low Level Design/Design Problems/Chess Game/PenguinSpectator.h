#ifndef PENGUIN_SPECTATOR_H
#define PENGUIN_SPECTATOR_H

#include "Spectator.h"

class PenguinSpectator : public Spectator {

public:

    PenguinSpectator(std::string id, std::string name);

    void update(std::string message) override;
};

#endif