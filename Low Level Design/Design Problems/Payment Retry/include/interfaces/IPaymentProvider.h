#ifndef I_PAYMENT_PROVIDER_H
#define I_PAYMENT_PROVIDER_H

#include <string>

#include "../entities/Payment.h"
#include "../entities/PaymentAttempt.h"

using namespace std;

class IPaymentProvider {

public:

    virtual PaymentAttempt processPayment(const Payment& payment, int attemptNumber) = 0;

    virtual string getProviderName() const = 0;

    virtual ~IPaymentProvider() = default;
    
};

#endif