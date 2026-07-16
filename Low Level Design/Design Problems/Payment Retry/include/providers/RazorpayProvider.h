#ifndef RAZORPAY_PROVIDER_H
#define RAZORPAY_PROVIDER_H

#include <queue>

#include "../interfaces/IPaymentProvider.h"

using namespace std;

class RazorpayProvider : public IPaymentProvider {

private:

    queue<FailureType> responses;

public:

    RazorpayProvider();

    void addMockResponse(FailureType response);

    PaymentAttempt processPayment(const Payment& payment, int attemptNumber) override;

    string getProviderName() const override;

};

#endif