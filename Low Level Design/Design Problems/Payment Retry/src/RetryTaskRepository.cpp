#include "../include/repositories/RetryTaskRepository.h"

void RetryTaskRepository::addTask(RetryTask* task) {

    retryQueue.push(task);
}

RetryTask* RetryTaskRepository::getNextTask() {

    if(retryQueue.empty()) {

        return nullptr;
    }

    return retryQueue.top();
}

RetryTask* RetryTaskRepository::popTask() {

    if (retryQueue.empty()) {

        return nullptr;
    }

    RetryTask* task = retryQueue.top();

    retryQueue.pop();

    return task;
}

bool RetryTaskRepository::isEmpty() const {

    return retryQueue.empty();
}

RetryTaskRepository::~RetryTaskRepository() {

    while(!retryQueue.empty()) {

        delete retryQueue.top();

        retryQueue.pop();
    }
}