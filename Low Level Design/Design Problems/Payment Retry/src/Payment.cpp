#include "../include/entities/Payment.h"

#include <ctime>

Payment::Payment(const string& paymentId, double amount, const string& currency, ProviderType providerType, const string& idempotencyKey) {

    this -> paymentId = paymentId;

    this -> amount = amount;

    this -> currency = currency;

    this -> providerType = providerType;

    this -> idempotencyKey = idempotencyKey;

    this -> status = PaymentStatus::PENDING;

    this -> retryCount = 0;

    this -> createdAt = time(nullptr);

    this -> updatedAt = this -> createdAt;
}

string Payment::getPaymentId() const {

    return paymentId;
}

double Payment::getAmount() const {

    return amount;
}

string Payment::getCurrency() const {

    return currency;
}

PaymentStatus Payment::getStatus() const {

    return status;
}

int Payment::getRetryCount() const {

    return retryCount;
}

ProviderType Payment::getProviderType() const {

    return providerType;
}

string Payment::getIdempotencyKey() const {

    return idempotencyKey;
}

long Payment::getCreatedAt() const {

    return createdAt;
}

long Payment::getUpdatedAt() const {

    return updatedAt;
}

void Payment::setStatus(PaymentStatus status) {

    this -> status = status;

    updateTimestamp();
}

void Payment::incrementRetryCount() {

    retryCount++;

    updateTimestamp();
}

void Payment::updateTimestamp() {

    updatedAt = time(nullptr);
}