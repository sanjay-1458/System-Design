#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "entities/RetryPolicy.h"

#include "providers/StripeProvider.h"
#include "providers/RazorpayProvider.h"

#include "repositories/PaymentRepository.h"
#include "repositories/HistoryRepository.h"
#include "repositories/RetryTaskRepository.h"

#include "services/PaymentService.h"
#include "services/ProviderService.h"
#include "services/HistoryService.h"
#include "services/RetryManager.h"
#include "services/RetryScheduler.h"
#include "services/PaymentProcessor.h"

using namespace std;


void executeRetries(PaymentProcessor& processor, RetryScheduler& scheduler) {

    while(!scheduler.isEmpty()) {

        vector<RetryTask*> tasks = scheduler.executeDueRetries();

        if(tasks.empty()) {

            this_thread::sleep_for(chrono::seconds(1));

            continue;
        }

        for(auto task: tasks) {

            processor.processPayment(task -> getPaymentId());

            delete task;
        }
    }
}

void printHistory(HistoryService& historyService, const string& paymentId) {

    cout << "\nHistory of ";

    cout << paymentId << "\n";

    auto history = historyService.getHistory(paymentId);

    for(auto attempt: history) {

        cout << "Attempt : " << attempt -> getAttemptNumber();

        cout << "\nStatus : " << (attempt -> getStatus() == AttemptStatus::SUCCESS ? "SUCCESS" : "FAILED");

        cout << "\nFailure : " << static_cast<int>(attempt -> getFailureType()) << endl;
    }

    cout << endl;
}

int main() {

   
    PaymentRepository paymentRepository;

    HistoryRepository historyRepository;

    RetryTaskRepository retryTaskRepository;

    PaymentService paymentService(&paymentRepository);

    ProviderService providerService;

    HistoryService historyService(&historyRepository);

    RetryPolicy retryPolicy(

        3,      // max retry

        2,      // base delay

        8,      // max delay

        2.0,    // multiplier

        true,   // jitter

        20      // jitter %
    );

    RetryManager retryManager(retryPolicy);

    RetryScheduler retryScheduler(&retryTaskRepository);

    PaymentProcessor paymentProcessor(&paymentService, &providerService, &historyService, &retryManager, &retryScheduler);
    
    StripeProvider* stripe = new StripeProvider();

    RazorpayProvider* razorpay = new RazorpayProvider();

    providerService.registerProvider(ProviderType::STRIPE, stripe);

    providerService.registerProvider(ProviderType::RAZORPAY, razorpay);

    /*
     * Success immediately
     */

    cout << "\nSuccess immediately\n";

    stripe -> addMockResponse(FailureType::NONE);

    paymentService.createPayment("PAY-1", 1000, "INR", ProviderType::STRIPE, "IDEMP-1");

    paymentProcessor.processPayment("PAY-1");

    printHistory(historyService, "PAY-1");

    /*
     * Fail once then Success
     */

    cout << "\nFail once then Success\n";

    stripe -> addMockResponse(FailureType::TIMEOUT);

    stripe -> addMockResponse(FailureType::NONE);

    paymentService.createPayment("PAY-2", 2000, "INR", ProviderType::STRIPE, "IDEMP-2");

    paymentProcessor.processPayment("PAY-2");

    executeRetries(paymentProcessor, retryScheduler);

    printHistory(historyService, "PAY-2");

    /*
     * Retry exhausted
     */

    cout << "\nRetry exhausted\n";

    stripe -> addMockResponse(FailureType::TIMEOUT);

    stripe -> addMockResponse(FailureType::NETWORK_ERROR);

    stripe -> addMockResponse(FailureType::SERVER_ERROR);

    stripe -> addMockResponse(FailureType::TIMEOUT);

    paymentService.createPayment("PAY-3", 3000, "INR", ProviderType::STRIPE, "IDEMP-3");

    paymentProcessor.processPayment("PAY-3");

    executeRetries(paymentProcessor, retryScheduler);

    printHistory(historyService, "PAY-3");

    /*
     * Non Retryable
     */

    cout << "\nNon Retryable\n";

    stripe -> addMockResponse(FailureType::INVALID_CARD);

    paymentService.createPayment("PAY-4", 5000, "INR", ProviderType::STRIPE, "IDEMP-4");

    paymentProcessor.processPayment("PAY-4");

    printHistory(historyService, "PAY-4");

    /*
     * Print History
     */

    cout << "\nHistory\n";

    printHistory(historyService, "PAY-3");

    /*
     * Razorpay
     */

    cout << "\nRazorpay Provider\n";

    razorpay -> addMockResponse(FailureType::NETWORK_ERROR);

    razorpay -> addMockResponse(FailureType::NONE);

    paymentService.createPayment("PAY-5", 7000, "INR", ProviderType::RAZORPAY, "IDEMP-5");

    paymentProcessor.processPayment("PAY-5");

    executeRetries(paymentProcessor, retryScheduler);

    printHistory(historyService, "PAY-5");

    return 0;
}