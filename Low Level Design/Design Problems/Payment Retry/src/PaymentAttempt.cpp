#include "../include/entities/PaymentAttempt.h"

#include <ctime>

PaymentAttempt::PaymentAttempt(const string& attemptId, const string& paymentId, int attemptNumber, ProviderType providerType) {

    this -> attemptId = attemptId;

    this -> paymentId = paymentId;

    this -> attemptNumber = attemptNumber;

    this -> providerType = providerType;

    this -> status = AttemptStatus::FAILED;

    this -> failureType = FailureType::NONE;

    this -> latency = 0;

    this -> attemptTime = time(nullptr);
}

string PaymentAttempt::getAttemptId() const {

    return attemptId;
}

string PaymentAttempt::getPaymentId() const {

    return paymentId;
}

int PaymentAttempt::getAttemptNumber() const {

    return attemptNumber;
}

ProviderType PaymentAttempt::getProviderType() const {

    return providerType;
}

AttemptStatus PaymentAttempt::getStatus() const {

    return status;
}

FailureType PaymentAttempt::getFailureType() const {

    return failureType;
}

string PaymentAttempt::getProviderTransactionId() const {

    return providerTransactionId;
}

string PaymentAttempt::getResponseCode() const {

    return responseCode;
}

long PaymentAttempt::getLatency() const {

    return latency;
}

long PaymentAttempt::getAttemptTime() const {

    return attemptTime;
}

void PaymentAttempt::setStatus(AttemptStatus status) {

    this -> status = status;
}

void PaymentAttempt::setFailureType(FailureType failureType) {

    this -> failureType = failureType;
}

void PaymentAttempt::setProviderTransactionId(const string& transactionId) {

    providerTransactionId = transactionId;
}

void PaymentAttempt::setResponseCode(const string& responseCode) {

    this -> responseCode = responseCode;
}

void PaymentAttempt::setLatency(long latency) {

    this -> latency = latency;
}