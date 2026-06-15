# Splitwise

The LLD pipeline for this problem will be as:
`Understand the system → Gathering Requirements → Use Cases (Who uses whom) → Entities → Relationships → Responsibilities → Classes & Interfaces → Design Patterns (If it is applicable) → Code.`


## Stage: 1 - Understand the system

Splitwise is a system where we track and manage the expenses among groups and track the shared expenses and who owes money to whom.

Instead of paying once for an event like "travel", here soemone pays and at the end, Splitwise calculates:

1. Who paid extra
2. Who paid less
3. Who owes money
4. How much each person should pay

and generates the minimum set of transactions needed to settle everything. (Nice-to-have feature not a Must-to-have and depends upon the problem)

### System Overview

User creates an account. A user can create a group and add members to it. A member can also leave a group. Users can add expenses to a group, where the expense can be split equally, by exact amounts, or by percentages. Each user can view who owes money to them and whom they owe money to. Users can settle their expenses. All transaction and settlements are logged in the transaction history, and notifications are sent whenever an expense is created or a settlement is made.

## Stage: 2 - Gathering Requirements

1. User creates an account.
2. User creates a group.
3. User can add / remove member from a group.
4. User can leave a group if no payment is due.
5. User can join a group.
6. User creates an Expense, either add it in group or with other user directly (1 to 1).
7. User can settle balance.
8. User can see balance and their transaction history.
9. Notification are sent when expense is created or settlement is made.
10. Debt simplification is supported and minimum transaction should be calculated.
11. Expense ca be updated or deleted.
12. Partial settlement is accepted.

## Stage: 3 - Use Cases (Who uses whom)

We need to find which `Actor`, perform which `Action` to achieve which `Goal`.


### Group Management

1. User creates a group.
2. User joins a group.
3. User adds / remove members from a group.
4. User leaves a group if no settlement exists.

### Expense Management

1. User creates an expense.
2. User updates / deletes an expense.
3. User chooses split type: equal, percentage, exact.
4. User add an expense in a group or between two users.

### Balance Management

1. User view their balance.
2. User views their transaction history.
3. User settles balance (complete or partial).

### Debt Simplification

1. User request debt simplification.
2. System calculate net balance.
3. System determines minimum transactions required.
4. System generates optimized settlements.

### Notification Flow

1. Expense created → notification sent.
2. Expense updated → notification sent.
3. Expense deleted → notification sent.
4. Settlement completed → notification sent.

## Stage: 4 - Entities

Now we find entities by finding nouns from use cases and filterting those having state and lifecycle along with business requirement. (Independent identity + lifecycle)

`Nouns`: thing, object(physical or logical item like group), person, or concept(may not exist physically but it is important to the business requirement).

Nouns:

1. Account
2. Group
3. Member
4. Expense
5. Balance
6. Settlement
7. Transaction History
8. Notification
9. Debt
10. Transaction
11. User

Account is merged with `User`, Balance is derived from `Expense` and `Settlement`, Transaction History is a list of `Expense` and `Settlement`, Debt is derived from `Balance` and Transaction can be formed from `Expense` and `Settlement`, Member is just a `User` in a `Group`.

Now to check our system we must check:
1. What data must survive? -> Entities

Or: `To identify the business objects that must exist for the system to work.`




For `Notification` we are not storing data like, here we are not storing `sent`, `read`. Therefore it is not an entity but a behaviour later we can add it as service.

### Entities

1. User
2. Group
3. Expense
4. ExpenseSplit
5. Settlement


## Stgae: 5 - Relationships

Here we find:

1. Which entities are connected.
2. What is the cardinality (One to One, One to Many, Many to Many).
3. Type of relationship (Association, Aggregation, Composition).

### Relationships
1. User - Group, Many to Many, Aggregation
2. Group - Expense, One to Many, Composition
3. User - Expense, One to Many, Association
4. Expense - ExpenseSplit, One to Many, Composition
5. User - ExpenseSplit, One to Many, Association
6. User - Settlement. One to Many, Association

## Stage: 6 - Responsibilities

We check each use case and see who owns the data and based on that we add create responsibility and allocate it the object who owns it we are not createing it from entities.

Use Case: `User adds member to group`, the meber is known by the Group thus:

Group Responsibility:
- Maintain members
- Add member
- Remove member


### Responsibilities

User Responsibilities:
- Maintain user information.
- Maintain joined groups.

Group Responsibilities:
- Maintain member list.
- Add member.
- Remove member.
- Validate join/leave operations.
- Maintain group expenses.

Expense Responsibilities:
- Maintain expense details.
- Maintain payer information.
- Maintain participants.
- Maintain split information.
- Update/Delete expense.

ExpenseSplit Responsibilities:
- Maintain participant share.
- Maintain share amount.

Settlement Responsibilities:
- Record settlement details.
- Record payer.
- Record receiver.
- Record settled amount.
- Support partial settlement.


## Stage: 7 - Classes & Interfaces

After having Entities and Responsibilities we can have:

### Entity Classes:
1. User
2. Group
3. Expense
4. ExpenseSplit
5. Settlement


Now, we can observe some responsibilities which does not belong to any entity like notification and debt simplification. So, this will exist as service hence: 

### Service Classes:
1. NotificationService
2. DebtSimplificationService

As here we don't store data and they only exist as behaviour.

1. What behavior must happen? -> Services
2. What data can be calculated? -> Derived models

Now, from our requirements we will only have one interface as we have multiple split types which can extend further.

### Interface:
1. SplitStrategy

### Implementations:
1. EqualSplitStrategy
2. ExactSplitStrategy
3. PercentageSplitStrategy

### User:
```json []
userId
name
email
List of Groups

joinGroup(Group)
leaveGroup(Group)
```

### Group:

```json []
groupId
name
List of Users (members)
List of Expense

addMember(User)
removeMember(User)
canLeave(User)
addExpense(Expense)
```

### Expense:

```json []
expenseId
amount
description
paidBy
List of Users (participants)
List of ExpenseSplit

updateExpense()
deleteExpense()
calculateSplit()
```

### ExpenseSplit:

```json []
user
shareAmount
```

### Settlement:
```json []
settlementId
payer
receiver
amount
timestamp

recordSettlement()
```

### NotificationService:

```json []
notifyExpenseCreated(Expense)
notifyExpenseUpdated(Expense)
notifyExpenseDeleted(Expense)
notifySettlement(Settlement)
```

### DebtSimplificationService:

```json []
calculateNetBalances(Group)
simplifyDebts(Group)
```

### SplitStrategy:

```json []
calculateSplit()
```


## Stage: 8 - Design Patterns

Since we have multuiple interchangeable split algorithm and using conditional is not effective as later it can have multiple algorithms. Here we will use `Strategy` pattern as we can later extend to more algorithms.

When expense are created or updated a notification is sent to multiple receivers here notification type can later become `email`, `sms`, etc. So, if it is inside Expense then whenever we update or extend Notification the Expense is also affected thus we willl use and `Observer` pattern.


## API Design

Now we will design resource oriented REST APIs.

After that we will find resources.

Primary resources -> Entities.
```json []
User
Group
Expense
Settlement
```

Now, what derived view we need.

1. View Balance
2. View Transaction History
3. Debt Simplification
4. Notifications

Resources:

```json []
/users
/groups
/expenses
/settlements
/balances
/transactions
/notifications
```

For every use-case we have APIs:

1. Create User: `POST /users`
```json []
{
  "name": "User-1",
  "email": "user1@gmail.com"
}
```
2. Get User: `GET /users/{userId}`
3. Get User Groups: `GET /users/{userId}/groups`
4. Create Group: `POST /groups`
```json []
{
  "name": "Goa Trip"
}
```
5. Get Group: `GET /groups/{groupId}`
6. Add Member: `POST /groups/{groupId}/members`
```json []
{
  "userId": "U1"
}
```
7. Remove Member: `DELETE /groups/{groupId}/members/{userId}`
8. Leave Group: `DELETE /groups/{groupId}/members/{userId}`
9. Get Members: `GET /groups/{groupId}/members`
10. Create Expense: `POST /expenses`
```json []
{
  "groupId": "G1",
  "paidBy": "U1",
  "amount": 3000,
  "description": "Hotel",
  "splitType": "EQUAL"
}
```
11. Get Expense: `GET /expenses/{expenseId}`
12. Update Expense: `PUT /expenses/{expenseId}`
13. Delete Expense: `DELETE /expenses/{expenseId}`
14. Get Group Expenses: `GET /groups/{groupId}/expenses`
15. Create Settlement: `POST /settlements`
```json []
{
  "payerId": "U2",
  "receiverId": "U1",
  "amount": 1000
}
```
16. Get Settlement: `GET /settlements/{settlementId}`
17. Group Settlement History: `GET /groups/{groupId}/settlements`
18. Get User Balances: `GET /users/{userId}/balances`
19. Get Group Balances: `GET /groups/{groupId}/balances`
20. User Transaction History: `GET /users/{userId}/transactions`
21. Group Transaction History: `GET /groups/{groupId}/transactions`
23. Simplify Debts: `POST /groups/{groupId}/simplify`
24. Get Simplified Settlement Plan: `GET /groups/{groupId}/simplify`
25. Get Notifications: `GET /users/{userId}/notifications`

## Database Design

The entities will almost become tables:
```json []
User
Group
Expense
ExpenseSplit
Settlement
```

Databases store state so we don't store services.

If system restarts, what must survive?

For Splitwise:
```json []
Users
Groups
Group Memberships
Expenses
Expense Splits
Settlements
```

Group member table exist because `User` to `Group` is Many-to-Many relationship thus we need a junction table.



















This is where balance calculation and DSA logic live.

Batch 5 (Coordinator)
Splitwise.h
Splitwise.cpp
Batch 6 (Driver)
main.cpp