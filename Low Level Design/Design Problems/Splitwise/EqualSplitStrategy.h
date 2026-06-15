#ifndef EQUAL_SPLIT_STRATEGY_H
#define EQUAL_SPLIT_STRATEGY_H

#include "SplitStrategy.h"

class EqualSplitStrategy : public SplitStrategy {

public:

    vector<ExpenseSplit*> calculateSplit(double amount, vector<User*>& participants) override;
};

#endif