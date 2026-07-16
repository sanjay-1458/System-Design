#include "../include/repositories/PaymentRepository.h"

void PaymentRepository::save(Payment* payment) {

    payments[payment -> getPaymentId()] = payment;
}

Payment* PaymentRepository::findById(const string& paymentId) {

    auto it = payments.find(paymentId);

    if(it == payments.end()) {

        return nullptr;
    }

    return it -> second;
}

bool PaymentRepository::exists(const string& paymentId) const {

    return payments.find(paymentId) != payments.end();
}

void PaymentRepository::remove(const string& paymentId) {

    auto it = payments.find(paymentId);

    if(it != payments.end()) {

        delete it -> second;

        payments.erase(it);
    }
}

vector<Payment*> PaymentRepository::findAll() {

    vector<Payment*> result;

    for(auto& entry: payments) {

        result.push_back(entry.second);
    }

    return result;
}

PaymentRepository::~PaymentRepository() {

    for(auto& entry: payments) {

        delete entry.second;
    }
}