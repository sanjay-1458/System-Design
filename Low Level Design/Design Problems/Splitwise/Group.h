#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

using namespace std;

class User;
class Expense;
class Settlement;

class Group {

private:

    string groupId;
    string name;
    vector<User*> members;
    vector<Expense*> expenses;
    vector<Settlement*> settlements;

public:

    Group(const string& groupId, const string& name);

    void addMember(User* user);
    void removeMember(User* user);
    bool canLeave(User* user);
    void addExpense(Expense* expense);
    void addSettlement(Settlement* settlement);

    string getGroupId() const;
    string getName() const;

    vector<User*>& getMembers();
    vector<Expense*>& getExpenses();
    vector<Settlement*>& getSettlements();
};

#endif