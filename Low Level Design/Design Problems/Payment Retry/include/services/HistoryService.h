#ifndef HISTORY_SERVICE_H
#define HISTORY_SERVICE_H

#include <string>
#include <vector>

#include "../repositories/HistoryRepository.h"

using namespace std;

class HistoryService {

private:

    HistoryRepository* historyRepository;

public:

    HistoryService(HistoryRepository* historyRepository);

    void recordAttempt(PaymentAttempt* attempt);

    vector<PaymentAttempt*> getHistory(const string& paymentId);
};

#endif