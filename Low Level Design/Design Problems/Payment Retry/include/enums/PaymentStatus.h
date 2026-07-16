#ifndef PAYMENT_STATUS_H
#define PAYMENT_STATUS_H

enum class PaymentStatus {
    
    PENDING,
    PROCESSING,
    RETRY_PENDING,
    SUCCESS,
    FAILED
};

#endif