#ifndef EXACT_SPLIT_STRATEGY_H
#define EXACT_SPLIT_STRATEGY_H

#include "SplitStrategy.h"

class ExactSplitStrategy : public SplitStrategy {

private:

    vector<double> exactAmounts;

public:

    ExactSplitStrategy(const vector<double>& exactAmounts);

    vector<ExpenseSplit*> calculateSplit(double amount, vector<User*>& participants) override;
};

#endif