# Payment Retry Mechanism

## Problem

A customer attempts to make a payment. The payment request is sent from our system to an external payment gateway. In the real world, payment gateways are not perfectly reliable. Sometimes they become temporarily unavailable, network calls fail, requests timeout, load balancers drop connections, internal services crash, or a response is lost while travelling back to our server. These failures may happen even when the customer's bank account has sufficient balance and the payment could eventually succeed if retried after some delay.

We need a payment processing system that communicates with an external payment gateway. When transient failures occur, the system should automatically recover through controlled retries. The system must ensure that customers are never charged multiple times, must handle uncertain outcomes safely, must avoid retry storms during outages, must maintain complete payment history, and must eventually reach a final consistent payment state.


## Gathering Requirements

