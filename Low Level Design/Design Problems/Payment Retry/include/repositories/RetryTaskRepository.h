#ifndef RETRY_TASK_REPOSITORY_H
#define RETRY_TASK_REPOSITORY_H

#include <queue>

#include "../entities/RetryTask.h"

using namespace std;

class RetryTaskComparator {

public:

    bool operator()(RetryTask* first, RetryTask* second) const {

        return first->getScheduledTime() > second->getScheduledTime();
    }
};

class RetryTaskRepository {

private:

    priority_queue<RetryTask*, vector<RetryTask*>, RetryTaskComparator> retryQueue;

public:

    void addTask(RetryTask* task);

    RetryTask* getNextTask();

    RetryTask* popTask();

    bool isEmpty() const;

    ~RetryTaskRepository();
};

#endif