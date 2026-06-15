#include "Settlement.h"

Settlement::Settlement(const string& settlementId, User* payer, User* receiver, double amount) : settlementId(settlementId), payer(payer), receiver(receiver), amount(amount) {

    timestamp = time(nullptr);
}

string Settlement::getSettlementId() const {

    return settlementId;
}

User* Settlement::getPayer() const {

    return payer;
}

User* Settlement::getReceiver() const {

    return receiver;
}

double Settlement::getAmount() const {

    return amount;
}

time_t Settlement::getTimestamp() const {

    return timestamp;
}