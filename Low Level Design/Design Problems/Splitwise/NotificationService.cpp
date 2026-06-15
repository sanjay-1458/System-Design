#include "NotificationService.h"

#include "Expense.h"
#include "Settlement.h"
#include "User.h"

#include <iostream>

using namespace std;

void NotificationService::notifyExpenseCreated(Expense* expense) {

    cout << "Expense Created : " << expense -> getDescription() << " Amount = " << expense -> getAmount() << endl;
}

void NotificationService::notifyExpenseUpdated(Expense* expense) {

    cout << "Expense Updated : " << expense -> getDescription() << endl;
}

void NotificationService::notifyExpenseDeleted(Expense* expense) {

    cout << "Expense Deleted : " << expense -> getDescription() << endl;
}

void NotificationService::notifySettlementCreated(Settlement* settlement) {

    cout << "Settlement : " << settlement -> getPayer() -> getName() << " paid " << settlement -> getReceiver() -> getName() << " Amount = " << settlement -> getAmount() << endl;
}