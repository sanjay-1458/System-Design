#ifndef SPLITWISE_H
#define SPLITWISE_H

#include <vector>
#include <string>

using namespace std;

class User;
class Group;
class Expense;
class Settlement;
class NotificationService;
class DebtSimplificationService;

class Splitwise {

private:

    vector<User*> users;
    vector<Group*> groups;
    NotificationService* notificationService;
    DebtSimplificationService* debtService;

public:

    Splitwise();

    ~Splitwise();

    void addUser(User* user);
    void createGroup(Group* group);

    User* getUser(string id);
    Group* getGroup(string id);

    void createExpense(Group* group, Expense* expense);
    void settle(Group* group, Settlement* settlement);
    void simplifyDebts(Group* group);
    void showBalances(Group* group);
};

#endif