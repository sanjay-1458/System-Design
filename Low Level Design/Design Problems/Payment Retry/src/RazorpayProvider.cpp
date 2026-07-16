#include "../include/providers/RazorpayProvider.h"

#include <chrono>

using namespace std;
using namespace chrono;

RazorpayProvider::RazorpayProvider() {}

void RazorpayProvider::addMockResponse(FailureType response) {

    responses.push(response);
}

PaymentAttempt RazorpayProvider::processPayment(const Payment& payment, int attemptNumber) {

    PaymentAttempt attempt(payment.getPaymentId() + "_" + to_string(attemptNumber), payment.getPaymentId(), attemptNumber, ProviderType::RAZORPAY);

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

    attempt.setProviderTransactionId("RAZORPAY_TXN_" + to_string(attemptNumber));

    auto end = steady_clock::now();

    attempt.setLatency(duration_cast<milliseconds>(end - start).count());

    return attempt;
}

string RazorpayProvider::getProviderName() const {

    return "Razorpay";
}