#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

using namespace std;

class User;
class ExpenseSplit;
class SplitStrategy;

class Expense {

private:

    string expenseId;
    string description;
    double amount;
    User* paidBy;
    vector<User*> participants;
    vector<ExpenseSplit*> splits;
    SplitStrategy* splitStrategy;
    bool isDeleted;

public:

    Expense(const string& expenseId, const string& description, double amount, User* paidBy, const vector<User*>& participants, SplitStrategy* splitStrategy);

    ~Expense();

    void calculateSplit();
    void updateExpense(const string& description, double amount);
    void deleteExpense();

    string getExpenseId() const;
    string getDescription() const;
    
    User* getPaidBy() const;
    
    vector<ExpenseSplit*>& getSplits();
    vector<User*>& getParticipants();
    
    double getAmount() const;
    bool getIsDeleted() const;
};

#endif