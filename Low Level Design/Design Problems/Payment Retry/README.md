# Payment Retry Mechanism

## Problem

A customer attempts to make a payment. The payment request is sent from our system to an external payment gateway. In the real world, payment gateways are not perfectly reliable. Sometimes they become temporarily unavailable, network calls fail, requests timeout, load balancers drop connections, internal services crash, or a response is lost while travelling back to our server. These failures may happen even when the customer's bank account has sufficient balance and the payment could eventually succeed if retried after some delay.

We need a payment processing system that communicates with an external payment gateway. When transient failures occur, the system should automatically recover through controlled retries. The system must ensure that customers are never charged multiple times, must handle uncertain outcomes safely, must avoid retry storms during outages, must maintain complete payment history, and must eventually reach a final consistent payment state.


## Gathering Requirements

The purpose of requirement gathering is to define the scope of the system before writing any design or code.

1. Three retry attempts.
2. Exponential backoff.
3. Random jitter.
4. Retry only temporary failures.
5. Store complete retry history.
6. Support multiple payment providers.
7. One retry worker.
8. Thread-safe design.


### Functional Requirements

These are the features the system must provide.

1. Create Payment

System receives a payment request. It creates a payment with a unique ID. Initially its status is PENDING.

2. Process Payment

The system sends the payment to the selected provider. Provider returns success or failure. Payment status is updated accordingly.

3. Support Multiple Providers

System should work with different payment gateways.

For example: 

Stripe, Razorpay, PayPal

Tomorrow another provider can be added without changing existing code.

4. Retry Temporary Failures

Not every failure should be retried.

Examples of retryable failures

```
timeout
network failure
server unavailable
gateway busy
connection reset
```
Examples of non-retryable failures
```
invalid card
card expired
insufficient balance
```
Retrying these wastes resources.

5. Maximum Retry Count

Retry only three times. After that, mark payment as permanently failed.


6. Exponential Backoff

Do not retry immediately. Increase waiting time after every failure.

Example
```
Retry 1 → wait 1 second

Retry 2 → wait 2 seconds

Retry 3 → wait 4 seconds
```
This prevents overloading the provider.


7. Random Jitter

Suppose 100,000 payments fail because Stripe goes down.

Without jitter, every payment retries exactly after 1 second.

The provider suddenly receives 100,000 requests together. This creates another outage. Instead, add a small random delay.

Example

Instead of exactly 2 seconds retry after

```
1.8
2.1
2.3
2.5
```
seconds.

The requests spread naturally. This is called jitter.

It avoids a retry storm.


8. Maintain Retry History

Every attempt should be stored.

Example
```
Attempt 1
Time
Provider
Failure reason
Latency
Response code
Result
```

9. Final Payment Status

At the end, payment must be one of: `[SUCCESS, FAILED]`

No payment should remain halfway forever.

10. Payment Idempotency

If the same payment request comes twice, system should not charge twice.

`Same payment ID -> Return existing result`.

Do not create another payment.


11. Provider Response Recording

Store
```
provider transaction ID
response code
error message
timestamp
latency
```

12. Retry Scheduling

After failure, payment should be scheduled for future retry. It should not block the current thread by sleeping. The scheduler decides when the next retry happens.

13. Query Payment

Client should be able to ask
```
Current status
Retry count
Retry history
Provider used
Final result
```

### Non-Functional Requirements

These describe how the system should behave rather than what it does.

1. Reliability

A retry should never be lost.

If the application crashes after scheduling a retry, a production system would recover and continue later. 

2. Scalability

Thousands of payments may be processed at the same time.
Retry mechanism should work independently for every payment.

3. Extensibility

Adding a new provider should require adding a new implementation rather than modifying existing processing logic.

4. Maintainability

Retry logic, provider logic, history, scheduling, and storage should each have a clear responsibility so they can be tested and modified independently.

5. Thread Safety

If multiple worker threads process payments, only one worker should retry a particular payment at a time. Shared state such as payment status and retry count must be protected from race conditions.

6. Performance

The system should avoid unnecessary retries, avoid blocking worker threads, and calculate retry delays efficiently.

7. Observability

Every retry attempt, delay, provider response, and final outcome should be logged or recorded so failures can be diagnosed later.

8. Configurability

Values such as maximum retry count, base delay, maximum delay, and jitter range should come from configuration rather than being hardcoded.