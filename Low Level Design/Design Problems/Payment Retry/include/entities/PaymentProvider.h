#ifndef PAYMENT_PROVIDER_H
#define PAYMENT_PROVIDER_H

#include <string>

#include "../enums/ProviderType.h"

using namespace std;

class PaymentProvider {

private:

    ProviderType providerType;

    string providerName;

    bool available;

public:

    PaymentProvider(ProviderType providerType, const string& providerName, bool available);

    ProviderType getProviderType() const;

    string getProviderName() const;

    bool isAvailable() const;

    void setAvailability(bool available);

};

#endif