#ifndef RETRY_POLICY_H
#define RETRY_POLICY_H

class RetryPolicy {

private:

    int maxRetries;

    long baseDelay;

    long maxDelay;

    double multiplier;

    bool jitterEnabled;

    int jitterPercentage;

public:

    RetryPolicy(int maxRetries, long baseDelay, long maxDelay, double multiplier, bool jitterEnabled, int jitterPercentage);

    int getMaxRetries() const;

    long getBaseDelay() const;

    long getMaxDelay() const;

    double getMultiplier() const;

    bool isJitterEnabled() const;

    int getJitterPercentage() const;

};

#endif