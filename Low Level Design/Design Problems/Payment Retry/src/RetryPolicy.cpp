#include "../include/entities/RetryPolicy.h"

RetryPolicy::RetryPolicy(int maxRetries, long baseDelay, long maxDelay, double multiplier, bool jitterEnabled, int jitterPercentage) {

    this -> maxRetries = maxRetries;

    this -> baseDelay = baseDelay;

    this -> maxDelay = maxDelay;

    this -> multiplier = multiplier;

    this -> jitterEnabled = jitterEnabled;

    this -> jitterPercentage = jitterPercentage;
}

int RetryPolicy::getMaxRetries() const {

    return maxRetries;
}

long RetryPolicy::getBaseDelay() const {

    return baseDelay;
}

long RetryPolicy::getMaxDelay() const {

    return maxDelay;
}

double RetryPolicy::getMultiplier() const {

    return multiplier;
}

bool RetryPolicy::isJitterEnabled() const {

    return jitterEnabled;
}

int RetryPolicy::getJitterPercentage() const {

    return jitterPercentage;
}