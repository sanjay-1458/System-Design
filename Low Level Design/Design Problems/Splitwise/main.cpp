#include <iostream>
#include <vector>

#include "Splitwise.h"

#include "User.h"
#include "Group.h"

#include "Expense.h"
#include "Settlement.h"

#include "SplitStrategy.h"
#include "EqualSplitStrategy.h"

using namespace std;

int main() {

    Splitwise splitwise;

    User* user1 = new User("U1", "User1", "user1@gmail.com");
    User* user2 = new User("U2", "User2", "user2@gmail.com");
    User* user3 = new User("U3", "User3", "user3@gmail.com");

    splitwise.addUser(user1);
    splitwise.addUser(user2);
    splitwise.addUser(user3);

    Group* tripGroup = new Group("G1", "Goa Trip");

    splitwise.createGroup(tripGroup);


    tripGroup -> addMember(user1);
    tripGroup -> addMember(user2);
    tripGroup -> addMember(user3);

    vector<User*> participants = {user1, user2, user3};

    SplitStrategy* strategy = new EqualSplitStrategy();

    Expense* hotelExpense = new Expense("E1", "Hotel", 3000, user1, participants, strategy);

    splitwise.createExpense(tripGroup, hotelExpense);
    splitwise.showBalances(tripGroup);

    Settlement* settlement = new Settlement("S1", user2, user1, 1000);

    splitwise.settle(tripGroup, settlement);
    splitwise.showBalances(tripGroup);
    splitwise.simplifyDebts(tripGroup);

    delete strategy;

    return 0;
}