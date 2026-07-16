#include "../include/providers/StripeProvider.h"

#include <chrono>

using namespace std;
using namespace chrono;

StripeProvider::StripeProvider() {}

void StripeProvider::addMockResponse(FailureType response) {

    responses.push(response);
}

PaymentAttempt StripeProvider::processPayment(const Payment& payment, int attemptNumber) {

    PaymentAttempt attempt(payment.getPaymentId() + "_" + to_string(attemptNumber), payment.getPaymentId(), attemptNumber, ProviderType::STRIPE);

    auto start = steady_clock::now();

    FailureType result = FailureType::NONE;

    if(!responses.empty()) {

        result = responses.front();

        responses.pop();
    }

    if(result == FailureType::NONE) {

        attempt.setStatus(AttemptStatus::SUCCESS);
    }
    else {

        attempt.setStatus(AttemptStatus::FAILED);

        attempt.setFailureType(result);
    }

    attempt.setResponseCode(result == FailureType::NONE ? "200" : "500");

    attempt.setProviderTransactionId("STRIPE_TXN_" + to_string(attemptNumber));

    auto end = steady_clock::now();

    attempt.setLatency(duration_cast<milliseconds>(end - start).count());

    return attempt;
}

string StripeProvider::getProviderName() const {

    return "Stripe";
}