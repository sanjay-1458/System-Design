#ifndef PAYMENT_ATTEMPT_H
#define PAYMENT_ATTEMPT_H

#include <string>

#include "../enums/AttemptStatus.h"
#include "../enums/FailureType.h"
#include "../enums/ProviderType.h"

using namespace std;

class PaymentAttempt {

private:

    string attemptId;

    string paymentId;

    int attemptNumber;

    ProviderType providerType;

    AttemptStatus status;

    FailureType failureType;

    string providerTransactionId;

    string responseCode;

    long latency;

    long attemptTime;

public:

    PaymentAttempt(const string& attemptId, const string& paymentId, int attemptNumber, ProviderType providerType);

    string getAttemptId() const;

    string getPaymentId() const;

    int getAttemptNumber() const;

    ProviderType getProviderType() const;

    AttemptStatus getStatus() const;

    FailureType getFailureType() const;

    string getProviderTransactionId() const;

    string getResponseCode() const;

    long getLatency() const;

    long getAttemptTime() const;

    void setStatus(AttemptStatus status);

    void setFailureType(FailureType failureType);

    void setProviderTransactionId(const string& transactionId);

    void setResponseCode(const string& responseCode);

    void setLatency(long latency);

};

#endif