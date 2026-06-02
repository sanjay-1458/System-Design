#include <iostream>

#include "PenguinSpectator.h"

PenguinSpectator::PenguinSpectator(std::string id, std::string name):Spectator(id, name) {
    
}

void PenguinSpectator::update(std::string message) {

    std::cout << "[Penguin] " << message << std::endl;
}