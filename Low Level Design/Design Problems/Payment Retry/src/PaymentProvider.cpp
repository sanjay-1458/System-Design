#include "../include/entities/PaymentProvider.h"

PaymentProvider::PaymentProvider(ProviderType providerType, const string& providerName, bool available) {

    this -> providerType = providerType;

    this -> providerName = providerName;

    this -> available = available;
}

ProviderType PaymentProvider::getProviderType() const {

    return providerType;
}

string PaymentProvider::getProviderName() const {

    return providerName;
}

bool PaymentProvider::isAvailable() const {

    return available;
}

void PaymentProvider::setAvailability(bool available) {

    this -> available = available;
}