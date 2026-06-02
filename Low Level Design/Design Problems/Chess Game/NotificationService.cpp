#include "NotificationService.h"

#include <algorithm>

void NotificationService::addObserver(Observer* observer) {

    observers.push_back(observer);
}

void NotificationService::removeObserver(Observer* observer) {

    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void NotificationService::notifyObservers(std::string message) {

    for(auto observer : observers) {

        observer -> update(message);
    }
}