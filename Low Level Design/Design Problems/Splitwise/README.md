# Splitwise

The LLD pipeline for this problem will be as:
`Understand the system → Gathering Requirements → Use Cases (Who uses whom) → Entities → Relationships → Responsibilities → Classes & Interfaces → Design Patterns (If it is applicable) → Edge Cases → Code.`


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
2. User updates / deletes and expense.
3. User chooses split type: equal, percentage, exact.
4. User add expense in a group or between two users.

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

Now we find entities by finding nouns from use cases and filterting those having state and lifecycle along with business requirement.

`Nouns`: thing, object(physical or logical item like group), person, or concept(may not exist physically but it is important to the business requirement).