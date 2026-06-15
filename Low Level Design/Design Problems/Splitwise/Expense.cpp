#include "Expense.h"

#include "User.h"
#include "ExpenseSplit.h"
#include "SplitStrategy.h"

#include <stdexcept>

Expense::Expense(const string& expenseId, const string& description, double amount, User* paidBy, const vector<User*>& participants, SplitStrategy* splitStrategy) : expenseId(expenseId), description(description), amount(amount), paidBy(paidBy), participants(participants), splitStrategy(splitStrategy), isDeleted(false) {
}

Expense::~Expense() {

    for(ExpenseSplit* split: splits) {

        delete split;
    }

    splits.clear();
}

void Expense::calculateSplit() {

    if(splitStrategy == nullptr) {

        throw runtime_error("Split strategy not configured");
    }

    for(ExpenseSplit* split: splits) {

        delete split;
    }

    splits.clear();

    splits = splitStrategy -> calculateSplit(amount, participants);
}

void Expense::updateExpense(const string& description, double amount) {

    this -> description = description;
    this -> amount = amount;

    calculateSplit();
}

void Expense::deleteExpense() {

    isDeleted = true;
}

string Expense::getExpenseId() const {

    return expenseId;
}

string Expense::getDescription() const {

    return description;
}

double Expense::getAmount() const {

    return amount;
}

User* Expense::getPaidBy() const {

    return paidBy;
}

vector<ExpenseSplit*>& Expense::getSplits() {

    return splits;
}

vector<User*>& Expense::getParticipants() {

    return participants;
}

bool Expense::getIsDeleted() const {

    return isDeleted;
}