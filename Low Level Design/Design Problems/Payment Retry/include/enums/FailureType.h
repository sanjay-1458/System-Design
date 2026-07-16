#ifndef FAILURE_TYPE_H
#define FAILURE_TYPE_H

enum class FailureType {
    
    NONE,

    NETWORK_ERROR,
    TIMEOUT,
    SERVER_ERROR,

    INVALID_CARD,
    INSUFFICIENT_FUNDS,
    FRAUD_DETECTED
};

#endif