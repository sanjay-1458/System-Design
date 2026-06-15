#include "Splitwise.h"

#include "User.h"
#include "Group.h"
#include "Expense.h"
#include "Settlement.h"

#include "NotificationService.h"
#include "DebtSimplificationService.h"

#include <iostream>

using namespace std;

Splitwise::Splitwise() {

    notificationService = new NotificationService();

    debtService = new DebtSimplificationService();
}

Splitwise::~Splitwise() {

    delete notificationService;
    delete debtService;

    for(User* user: users) {

        delete user;
    }

    for(Group* group: groups) {

        delete group;
    }
}

void Splitwise::addUser(User* user) {

    users.push_back(user);
}

void Splitwise::createGroup(Group* group) {

    groups.push_back(group);
}

User* Splitwise::getUser(string id) {

    for(User* user: users) {

        if(user -> getUserId() == id) {

            return user;
        }
    }

    return nullptr;
}

Group* Splitwise::getGroup(string id) {

    for(Group* group: groups) {

        if(group -> getGroupId() == id) {

            return group;
        }
    }

    return nullptr;
}

void Splitwise::createExpense(Group* group, Expense* expense) {

    if(group == nullptr || expense == nullptr) {

        return;
    }

    expense -> calculateSplit();

    group -> addExpense(expense);

    notificationService -> notifyExpenseCreated(expense);
}

void Splitwise::settle(Group* group, Settlement* settlement) {

    if(group == nullptr || settlement == nullptr) {

        return;
    }

    group -> addSettlement(settlement);

    notificationService -> notifySettlementCreated(settlement);
}

void Splitwise::showBalances(Group* group) {

    if(group == nullptr) {

        return;
    }

    auto balances = debtService -> calculateNetBalances(group);

    for(auto& entry: balances) {

        cout << entry.first -> getName() << " : " << entry.second << endl;
    }

    cout << endl;
}

void Splitwise::simplifyDebts(Group* group) {

    if(group == nullptr) {

        return;
    }

    vector<Settlement*> settlements = debtService -> simplifyDebts(group);


    for(Settlement* settlement: settlements) {

        cout << settlement -> getPayer() -> getName() << " pays " << settlement -> getReceiver() -> getName() << " : " << settlement -> getAmount() << endl;
    }

    cout << endl;

    for(Settlement* settlement: settlements) {

        delete settlement;
    }
}