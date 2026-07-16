#include "../include/services/ProviderService.h"

#include <stdexcept>

void ProviderService::registerProvider(ProviderType providerType, IPaymentProvider* provider) {

    providers[providerType] = provider;
}

IPaymentProvider* ProviderService::getProvider(ProviderType providerType) {

    auto it = providers.find(providerType);

    if(it == providers.end()) {

        return nullptr;
    }

    return it -> second;
}

PaymentAttempt ProviderService::processPayment(const Payment& payment, int attemptNumber) {

    IPaymentProvider* provider = getProvider(payment.getProviderType());

    if(provider == nullptr) {

        throw runtime_error("Provider not registered.");
    }

    return provider -> processPayment(payment, attemptNumber);
}

ProviderService::~ProviderService() {

    for(auto& entry: providers) {

        delete entry.second;
    }
}