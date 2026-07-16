#include "../include/services/RetryScheduler.h"

#include <ctime>

RetryScheduler::RetryScheduler(RetryTaskRepository* retryTaskRepository) {

    this -> retryTaskRepository = retryTaskRepository;
}

void RetryScheduler::scheduleRetry(RetryTask* retryTask) {

    if(retryTask == nullptr) {

        return;
    }

    retryTaskRepository -> addTask(retryTask);
}

vector<RetryTask*> RetryScheduler::executeDueRetries() {

    vector<RetryTask*> readyTasks;

    long currentTime = time(nullptr);

    while(!retryTaskRepository -> isEmpty()) {

        RetryTask* task = retryTaskRepository -> getNextTask();

        if(task -> getScheduledTime() > currentTime) {

            break;
        }

        readyTasks.push_back(task);

        retryTaskRepository -> popTask();
    }

    return readyTasks;
}

void RetryScheduler::removeRetryTask() {

    retryTaskRepository -> popTask();
}

bool RetryScheduler::isEmpty() const {

    return retryTaskRepository->isEmpty();
}