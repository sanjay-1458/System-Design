#ifndef EXPENSE_SPLIT_H
#define EXPENSE_SPLIT_H

class User;

class ExpenseSplit {

private:

    User* user;
    double shareAmount;

public:

    ExpenseSplit(User* user, double shareAmount);

    User* getUser() const;

    double getShareAmount() const;
};

#endif