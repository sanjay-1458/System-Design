#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

class Expense;
class Settlement;

class NotificationService {

public:

    void notifyExpenseCreated(Expense* expense);
    void notifyExpenseUpdated(Expense* expense);
    void notifyExpenseDeleted(Expense* expense);
    void notifySettlementCreated(Settlement* settlement);
};

#endif