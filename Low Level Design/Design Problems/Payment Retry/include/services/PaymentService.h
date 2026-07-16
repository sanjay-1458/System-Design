#ifndef PAYMENT_SERVICE_H
#define PAYMENT_SERVICE_H

#include <string>

#include "../entities/Payment.h"
#include "../repositories/PaymentRepository.h"

using namespace std;

class PaymentService {

private:

    PaymentRepository* paymentRepository;

public:

    PaymentService(PaymentRepository* paymentRepository);

    Payment* createPayment(const string& paymentId, double amount, const string& currency, ProviderType providerType, const string& idempotencyKey);

    Payment* findPayment(const string& paymentId);

    void updateStatus(const string& paymentId, PaymentStatus status);

    void incrementRetryCount(const string& paymentId);
};

#endif