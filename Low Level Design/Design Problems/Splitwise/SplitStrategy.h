#ifndef SPLIT_STRATEGY_H
#define SPLIT_STRATEGY_H

#include <vector>

using namespace std;

class User;
class ExpenseSplit;

class SplitStrategy {

public:

    virtual vector<ExpenseSplit*> calculateSplit(double amount, vector<User*>& participants) = 0;

    virtual ~SplitStrategy() {}
};

#endif