#ifndef PAYMENT_REPOSITORY_H
#define PAYMENT_REPOSITORY_H

#include <string>
#include <vector>
#include <unordered_map>

#include "../entities/Payment.h"

using namespace std;

class PaymentRepository {

private:

    unordered_map<string, Payment*> payments;

public:

    void save(Payment* payment);

    Payment* findById(const string& paymentId);

    bool exists(const string& paymentId) const;

    void remove(const string& paymentId);

    vector<Payment*> findAll();

    ~PaymentRepository();
};

#endif