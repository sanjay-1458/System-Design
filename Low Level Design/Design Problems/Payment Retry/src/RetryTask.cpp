#include "../include/entities/RetryTask.h"

RetryTask::RetryTask(const string& paymentId, int retryNumber, long scheduledTime) {

    this->paymentId = paymentId;

    this->retryNumber = retryNumber;

    this->scheduledTime = scheduledTime;
}

string RetryTask::getPaymentId() const {

    return paymentId;
}

int RetryTask::getRetryNumber() const {

    return retryNumber;
}

long RetryTask::getScheduledTime() const {

    return scheduledTime;
}