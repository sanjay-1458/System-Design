#ifndef STRIPE_PROVIDER_H
#define STRIPE_PROVIDER_H

#include <queue>

#include "../interfaces/IPaymentProvider.h"

using namespace std;

class StripeProvider : public IPaymentProvider {

private:

    queue<FailureType> responses;

public:

    StripeProvider();

    void addMockResponse(FailureType response);

    PaymentAttempt processPayment(const Payment& payment, int attemptNumber) override;

    string getProviderName() const override;

};

#endif