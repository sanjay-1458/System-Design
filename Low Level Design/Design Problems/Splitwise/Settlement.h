#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <string>
#include <ctime>

using namespace std;

class User;

class Settlement {

private:

    string settlementId;
    User* payer;
    User* receiver;
    double amount;
    time_t timestamp;

public:

    Settlement(const string& settlementId, User* payer, User* receiver, double amount);

    string getSettlementId() const;

    User* getPayer() const;
    User* getReceiver() const;

    double getAmount() const;
    time_t getTimestamp() const;
};

#endif