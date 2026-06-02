#ifndef BROADCAST_SPECTATOR_H
#define BROADCAST_SPECTATOR_H

#include "Spectator.h"

class BroadcastSpectator : public Spectator {

public:

    BroadcastSpectator(std::string id, std::string name);

    void update(std::string message) override;
};

#endif