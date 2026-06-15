#include "Group.h"

#include "User.h"
#include "Expense.h"
#include "Settlement.h"

#include <algorithm>

Group::Group(const string& groupId, const string& name) : groupId(groupId), name(name) {
}

void Group::addMember(User* user) {

    if(user == nullptr) {

        return;
    }

    auto it = find(members.begin(), members.end(), user);

    if(it == members.end()) {

        members.push_back(user);

        user -> joinGroup(this);
    }
}

void Group::removeMember(User* user) {

    if(!canLeave(user)) {

        return;
    }

    auto it = find(members.begin(), members.end(), user);

    if(it != members.end()) {

        members.erase(it);

        user -> leaveGroup(this);
    }
}

bool Group::canLeave(User* user) {

    if(user == nullptr) {

        return false;
    }

    return true;
}

void Group::addExpense(Expense* expense) {

    if(expense == nullptr) {

        return;
    }

    expenses.push_back(expense);
}

void Group::addSettlement(Settlement* settlement) {

    if(settlement == nullptr) {

        return;
    }

    settlements.push_back(settlement);
}

string Group::getGroupId() const {

    return groupId;
}

string Group::getName() const {

    return name;
}

vector<User*>& Group::getMembers() {

    return members;
}

vector<Expense*>& Group::getExpenses() {

    return expenses;
}

vector<Settlement*>& Group::getSettlements() {

    return settlements;
}