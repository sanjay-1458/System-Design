#include <iostream>

#include "BroadcastSpectator.h"

BroadcastSpectator::BroadcastSpectator(std::string id, std::string name):Spectator(id, name) {
    
}

void BroadcastSpectator::update(std::string message) {

    std::cout << "[Broadcast] " << message << std::endl;
}