#ifndef PROVIDER_SERVICE_H
#define PROVIDER_SERVICE_H

#include <unordered_map>

#include "../interfaces/IPaymentProvider.h"
#include "../enums/ProviderType.h"

using namespace std;

class ProviderService {

private:

    unordered_map<ProviderType, IPaymentProvider*> providers;

public:

    void registerProvider(ProviderType providerType, IPaymentProvider* provider);

    IPaymentProvider* getProvider(ProviderType providerType);

    PaymentAttempt processPayment(const Payment& payment, int attemptNumber);

    ~ProviderService();
};

#endif