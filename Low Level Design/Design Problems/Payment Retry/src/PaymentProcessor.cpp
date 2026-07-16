#include "../include/services/PaymentProcessor.h"

PaymentProcessor::PaymentProcessor(PaymentService* paymentService, ProviderService* providerService, HistoryService* historyService, RetryManager* retryManager, RetryScheduler* retryScheduler) {

    this -> paymentService = paymentService;

    this -> providerService = providerService;

    this -> historyService = historyService;

    this -> retryManager = retryManager;

    this -> retryScheduler = retryScheduler;
}

void PaymentProcessor::processPayment(const std::string& paymentId) {

    Payment* payment = paymentService -> findPayment(paymentId);

    if(payment == nullptr) {

        return;
    }

    paymentService -> updateStatus(paymentId, PaymentStatus::PROCESSING);

    PaymentAttempt attempt = providerService -> processPayment(*payment, payment -> getRetryCount() + 1);

    historyService -> recordAttempt(new PaymentAttempt(attempt));

    if(attempt.getStatus() == AttemptStatus::SUCCESS) {

        handleSuccess(payment, attempt);
    }
    else {

        handleFailure(payment, attempt);
    }
}

void PaymentProcessor::handleSuccess(Payment* payment, PaymentAttempt& attempt) {

    paymentService -> updateStatus(payment -> getPaymentId(), PaymentStatus::SUCCESS);
}

void PaymentProcessor::handleFailure(Payment* payment, PaymentAttempt& attempt) {

    if(!retryManager -> canRetry(*payment, attempt)) {

        paymentService -> updateStatus(payment -> getPaymentId(), PaymentStatus::FAILED);

        return;
    }

    paymentService -> incrementRetryCount(payment -> getPaymentId());

    paymentService -> updateStatus(payment -> getPaymentId(), PaymentStatus::RETRY_PENDING);

    RetryTask* retryTask = retryManager -> createRetryTask(*payment);

    retryScheduler -> scheduleRetry(retryTask);
}