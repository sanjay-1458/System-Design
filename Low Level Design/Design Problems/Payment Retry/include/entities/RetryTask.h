#ifndef RETRY_TASK_H
#define RETRY_TASK_H

#include <string>

using namespace std;

class RetryTask {

private:

    string paymentId;

    int retryNumber;

    long scheduledTime;

public:

    RetryTask(const string& paymentId, int retryNumber, long scheduledTime);

    string getPaymentId() const;

    int getRetryNumber() const;

    long getScheduledTime() const;

};

#endif