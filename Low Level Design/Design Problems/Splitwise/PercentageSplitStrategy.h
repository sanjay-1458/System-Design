#ifndef PERCENTAGE_SPLIT_STRATEGY_H
#define PERCENTAGE_SPLIT_STRATEGY_H

#include "SplitStrategy.h"

class PercentageSplitStrategy : public SplitStrategy {

private:

    vector<double> percentages;

public:

    PercentageSplitStrategy(const vector<double>& percentages);

    vector<ExpenseSplit*> calculateSplit(double amount, vector<User*>& participants) override;
};

#endif