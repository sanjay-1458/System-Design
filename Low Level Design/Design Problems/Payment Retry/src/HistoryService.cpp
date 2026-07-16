#include "../include/services/HistoryService.h"

HistoryService::HistoryService(HistoryRepository* historyRepository) {

    this -> historyRepository = historyRepository;
}

void HistoryService::recordAttempt(PaymentAttempt* attempt) {

    if(attempt == nullptr) {

        return;
    }

    historyRepository -> saveAttempt(attempt);
}

vector<PaymentAttempt*> HistoryService::getHistory(const string& paymentId) {

    return historyRepository -> getAttempts(paymentId);
}