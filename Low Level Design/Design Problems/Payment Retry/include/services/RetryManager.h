#ifndef RETRY_MANAGER_H
#define RETRY_MANAGER_H

#include "../entities/RetryPolicy.h"
#include "../entities/RetryTask.h"
#include "../entities/Payment.h"
#include "../entities/PaymentAttempt.h"

class RetryManager {

private:

    RetryPolicy retryPolicy;

public:

    RetryManager(const RetryPolicy& retryPolicy);

    bool canRetry(const Payment& payment, const PaymentAttempt& attempt) const;

    bool isRetryableFailure(FailureType failureType) const;

    long applyExponentialBackoff(int retryCount) const;

    long applyJitter(long delay) const;

    long calculateDelay(int retryCount) const;

    RetryTask* createRetryTask(const Payment& payment) const;
};

#endif