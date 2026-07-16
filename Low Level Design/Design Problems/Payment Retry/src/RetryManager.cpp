#include "../include/services/RetryManager.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

RetryManager::RetryManager(const RetryPolicy& retryPolicy) : retryPolicy(retryPolicy) {

    srand(time(nullptr));
}

bool RetryManager::canRetry(const Payment& payment, const PaymentAttempt& attempt) const {

    if(!isRetryableFailure(attempt.getFailureType())) {

        return false;
    }

    return payment.getRetryCount() < retryPolicy.getMaxRetries();
}

bool RetryManager::isRetryableFailure(FailureType failureType) const {

    switch(failureType) {

        case FailureType::NETWORK_ERROR:

        case FailureType::TIMEOUT:

        case FailureType::SERVER_ERROR:

            return true;

        default:

            return false;
    }
}

long RetryManager::applyExponentialBackoff(int retryCount) const {

    double delay = retryPolicy.getBaseDelay() * pow(retryPolicy.getMultiplier(), retryCount);

    if(delay > retryPolicy.getMaxDelay()) {

        delay = retryPolicy.getMaxDelay();
    }

    return static_cast<long>(delay);
}

long RetryManager::applyJitter(long delay) const {

    if(!retryPolicy.isJitterEnabled()) {

        return delay;
    }

    int percentage = retryPolicy.getJitterPercentage();

    long variation = (delay * percentage) / 100;

    long randomValue = rand() % (variation * 2 + 1);

    return delay - variation + randomValue;
}

long RetryManager::calculateDelay(int retryCount) const {

    long delay = applyExponentialBackoff(retryCount);

    return applyJitter(delay);
}

RetryTask* RetryManager::createRetryTask(const Payment& payment) const {

    long delay = calculateDelay(payment.getRetryCount());

    long scheduledTime = time(nullptr) + delay;

    return new RetryTask(payment.getPaymentId(), payment.getRetryCount() + 1, scheduledTime);
}