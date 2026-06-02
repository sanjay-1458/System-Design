#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <string>

#include "Observer.h"

class Spectator : public Observer {

protected:

    std::string id;

    std::string name;

public:

    Spectator(std::string id, std::string name);

    virtual void update(std::string message) = 0;

    virtual ~Spectator() = default;
};

#endif