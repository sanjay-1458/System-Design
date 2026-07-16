#ifndef HISTORY_REPOSITORY_H
#define HISTORY_REPOSITORY_H

#include <unordered_map>
#include <vector>
#include <string>

#include "../entities/PaymentAttempt.h"

using namespace std;

class HistoryRepository {

private:

    unordered_map<string, vector<PaymentAttempt*>> history;

public:

    void saveAttempt(PaymentAttempt* attempt);

    vector<PaymentAttempt*> getAttempts(const string& paymentId);

    ~HistoryRepository();
};

#endif