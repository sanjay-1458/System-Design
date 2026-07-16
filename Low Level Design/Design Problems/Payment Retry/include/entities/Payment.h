#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

#include "../enums/PaymentStatus.h"
#include "../enums/ProviderType.h"

using namespace std;

class Payment {

private:

    string paymentId;

    double amount;

    string currency;

    PaymentStatus status;

    int retryCount;

    string idempotencyKey;

    ProviderType providerType;

    long createdAt;

    long updatedAt;

public:

    Payment(const string& paymentId, double amount, const string& currency, ProviderType providerType, const string& idempotencyKey);

    string getPaymentId() const;

    double getAmount() const;

    string getCurrency() const;

    PaymentStatus getStatus() const;

    int getRetryCount() const;

    ProviderType getProviderType() const;

    string getIdempotencyKey() const;

    long getCreatedAt() const;

    long getUpdatedAt() const;

    void setStatus(PaymentStatus status);

    void incrementRetryCount();

    void updateTimestamp();

};

#endif