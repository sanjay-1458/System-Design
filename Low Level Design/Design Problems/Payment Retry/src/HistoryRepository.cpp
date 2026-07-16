#include "../include/repositories/HistoryRepository.h"

void HistoryRepository::saveAttempt(PaymentAttempt* attempt) {

    history[attempt -> getPaymentId()].push_back(attempt);
}

vector<PaymentAttempt*> HistoryRepository::getAttempts(const string& paymentId) {

    return history[paymentId];
}

HistoryRepository::~HistoryRepository() {

    for(auto& entry: history) {

        for(auto attempt: entry.second) {

            delete attempt;
        }
    }
}