#include "EqualSplitStrategy.h"
#include "ExpenseSplit.h"
#include "User.h"

#include <stdexcept>

vector<ExpenseSplit*> EqualSplitStrategy::calculateSplit(double amount, vector<User*>& participants) {

    if(participants.empty()) {

        throw invalid_argument("Participants cannot be empty");
    }

    vector<ExpenseSplit*> splits;

    double share = amount / participants.size();

    for(User* user: participants) {

        splits.push_back(new ExpenseSplit(user, share));
    }

    return splits;
}