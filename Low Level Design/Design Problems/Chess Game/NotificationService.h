#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <vector>
#include <string>

#include "Observer.h"

class NotificationService {

private:

    std::vector<Observer*> observers;

public:

    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);

    void notifyObservers(std::string message);
};

#endif