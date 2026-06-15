#include "ExpenseSplit.h"

ExpenseSplit::ExpenseSplit(User* user, double shareAmount) : user(user), shareAmount(shareAmount) {
}

User* ExpenseSplit::getUser() const {

    return user;
}

double ExpenseSplit::getShareAmount() const {

    return shareAmount;
}