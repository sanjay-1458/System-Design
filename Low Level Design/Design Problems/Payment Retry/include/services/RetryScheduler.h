#ifndef RETRY_SCHEDULER_H
#define RETRY_SCHEDULER_H

#include <vector>

#include "../repositories/RetryTaskRepository.h"

using namespace std;

class RetryScheduler {

private:

    RetryTaskRepository* retryTaskRepository;

public:

    RetryScheduler(RetryTaskRepository* retryTaskRepository);

    void scheduleRetry(RetryTask* retryTask);

    vector<RetryTask*> executeDueRetries();

    void removeRetryTask();

    bool isEmpty() const;
};

#endif