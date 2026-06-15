#include "ExactSplitStrategy.h"
#include "ExpenseSplit.h"
#include "User.h"

#include <stdexcept>

ExactSplitStrategy::ExactSplitStrategy(const vector<double>& exactAmounts) : exactAmounts(exactAmounts) {}

vector<ExpenseSplit*> ExactSplitStrategy::calculateSplit(double amount, vector<User*>& participants) {

    if(participants.size() != exactAmounts.size()) {

        throw invalid_argument("Participants and amounts mismatch");
    }

    double total = 0.0;

    for(double value: exactAmounts) {

        total += value;
    }

    if(total != amount) {

        throw invalid_argument("Exact split total must equal expense amount");
    }

    vector<ExpenseSplit*> splits;

    for(int i = 0; i < participants.size(); ++i) {

        splits.push_back(new ExpenseSplit(participants[i], exactAmounts[i]));
    }

    return splits;
}