#include "PercentageSplitStrategy.h"
#include "ExpenseSplit.h"
#include "User.h"

#include <stdexcept>

PercentageSplitStrategy::PercentageSplitStrategy(const vector<double>& percentages) : percentages(percentages) {
}

vector<ExpenseSplit*> PercentageSplitStrategy::calculateSplit(double amount, vector<User*>& participants) {

    if(participants.size() != percentages.size()) {

        throw invalid_argument("Participants and percentages mismatch");
    }

    double percentageSum = 0.0;

    for(double percentage: percentages) {

        percentageSum += percentage;
    }

    if(percentageSum != 100.0) {

        throw invalid_argument("Percentages must sum to 100");
    }

    vector<ExpenseSplit*> splits;

    for(int i = 0; i < participants.size(); i++) {

        double shareAmount = (amount * percentages[i]) / 100.0;

        splits.push_back(new ExpenseSplit(participants[i], shareAmount));
    }

    return splits;
}