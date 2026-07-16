#ifndef PAYMENT_PROCESSOR_H
#define PAYMENT_PROCESSOR_H

#include "PaymentService.h"
#include "ProviderService.h"
#include "HistoryService.h"
#include "RetryManager.h"
#include "RetryScheduler.h"

class PaymentProcessor {

private:

    PaymentService* paymentService;

    ProviderService* providerService;

    HistoryService* historyService;

    RetryManager* retryManager;

    RetryScheduler* retryScheduler;

public:

    PaymentProcessor(PaymentService* paymentService, ProviderService* providerService, HistoryService* historyService, RetryManager* retryManager, RetryScheduler* retryScheduler);

    void processPayment(const std::string& paymentId);

private:

    void handleSuccess(Payment* payment, PaymentAttempt& attempt);

    void handleFailure(Payment* payment, PaymentAttempt& attempt);
};

#endif