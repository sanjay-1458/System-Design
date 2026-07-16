#include "../include/services/PaymentService.h"

PaymentService::PaymentService(PaymentRepository* paymentRepository) {

    this -> paymentRepository = paymentRepository;
}

Payment* PaymentService::createPayment(const string& paymentId, double amount, const string& currency, ProviderType providerType, const string& idempotencyKey) {

    Payment* payment = new Payment(paymentId, amount, currency, providerType, idempotencyKey);

    paymentRepository -> save(payment);

    return payment;
}

Payment* PaymentService::findPayment(const string& paymentId) {

    return paymentRepository -> findById(paymentId);
}

void PaymentService::updateStatus(const string& paymentId, PaymentStatus status) {

    Payment* payment = paymentRepository -> findById(paymentId);

    if(payment == nullptr) {

        return;
    }

    payment -> setStatus(status);
}

void PaymentService::incrementRetryCount(const string& paymentId) {

    Payment* payment = paymentRepository -> findById(paymentId);

    if(payment == nullptr) {

        return;
    }

    payment -> incrementRetryCount();
}