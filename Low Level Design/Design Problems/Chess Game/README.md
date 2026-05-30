# Overview

Objective is to convert a vague business problem into a maintainable object-oriented design. Like when an interviewer says "Design a Chess Game", there can be many things like concurrent games, multiplayer, game rules, score, types of games, distributed design, etc., which we can't do all in a fixed time. For that purpose, we divide the process into multiple stages. Each stage is dedicated to one aspect and acts as a base for the next stages.

LLD pipeline:

Gathering Requirements → Use Cases (Who uses whom) → Entities → Relationships → Responsibilities → Classes → Interfaces → Design Patterns (If it is applicable) → Edge Cases → Code.

## Stage 1 : Understanding Functional Requirements

This is the most important stage because every design decision comes from requirements. If requirements are wrong, everything else becomes wrong. It also helps us in discovering how a new system works if we are unaware of it. For example, if someone does not know about "Splitwise", they can get a high-level understanding and design the minimal required features.


Examples:

1. For Parking Lot:

```
Use cases become:

1. Vehicle enters
2. Ticket generated
3. Spot allocated
4. Vehicle exits
5. Payment calculated
6. Spot released
```

2. For BookMyShow:

```
Use cases become:

1. Search movie
2. Select show
3. Book seats
4. Pay
5. Cancel booking
```


## Stage 2 : Identify Actors and Use Cases

After understanding functionality, identify who interacts with the system and who is triggering those actions.

Example:

In a parking lot, a `Driver` enters parking and exits parking, and an `Admin` adds floors, and `Floors` add parking spots.

## Stage 3 : Identifying Entities

Now, based on the functional requirements, we need to find core business objects, so we will take the requirements and highlight nouns. Two important things we need are: nouns and verbs. (`nouns`: A noun is a person, place, thing, concept, or object mentioned in the problem statement. `verbs`: Methods or behaviour)

Example:

In `"A customer can place an order. An order contains products. Payment is made for an order."`

Nouns:
1. Customer
2. Order
3. Products
4. Payment

Verbs:
1. Customer.placeOrder()
2. Order contains Product
3. Payment.payForOrder()

In `"A library manages books. Members borrow books and return them."`

Nouns:
1. Library
2. Books
3. Members

Verbs:
1. Library manages books
2. Member.borrowBooks()
3. Member.returnBooks()


### Note:
Not every noun becomes an entity. Some nouns are just attributes.

In `"A user has a name, email, and phone number."`

Nouns:
1. User

Attributes:
1. Name
2. Email
3. Phone Number

#### Not every noun should become a class.

1. Address might simply be a value object.
2. Status might be an enum.


## Stage 4 : Finding Relationships Between Entities

Now we need to think about how entities are connected with each other.

Example:

In Parking Lot:

```
Parking Lot contains Floor
Floor contains Spots
Spot holds Vehicle
Vehicle owns Ticket
Ticket has Payment
```

### Has-A Relationship

```
Car has Engine
Ticket has Payment
Show has Seats
```

### Is-A Relationship

```
Car is a Vehicle
Truck is a Vehicle
Bike is a Vehicle
```


## Stage 5 : Assigning Responsibilities

Here we need to assign responsibility to the exact entities, as "who should own this responsibility".

Example:

Payment calculation:

Should Vehicle calculate payment? No. PaymentService should.


### Data and behavior should stay together.
If Ticket contains entry time and exit time, Ticket may calculate duration. But finding available spots should not belong to Ticket.

## Stage 6 : Designing Classes and Attributes

Once responsibilities are clear.

Each class should be able to answer:

1. What data do I hold?
2. What behavior do I provide?

Example:

`[Vehicle]`

Attributes:
1. vehicleNumber
2. vehicleType

Methods:
1. getVehicleType()


## Stage 7 : Finding Abstractions and Interfaces

Now, we must design extensible code. For that, we will think about what might change in the future.
Anything that changes frequently should be abstracted.

Example:

If we have a Payment entity, the payment method might change in the future, like someone may use `UPI`, `Wallet`, or `Net Banking`. For this, we must create a `PaymentStrategy`.


## Stage 8 : Applying Design Patterns

We should not force any design pattern unless we are facing a problem.

Here we have multiple payment options; therefore, the `Strategy` pattern comes into action, `Factory` for creating objects and separating object creation from business logic, `Singleton` for creating only one instance in the system like a global manager, `Observer` for notifications, `Builder` when a class has many constructor parameters, etc.

## Stage 9 : Handling Edge Cases

We must be able to think about what can go wrong.

Like in Parking Lot, what if there is `"No spot available"` or an `"Invalid ticket"`?


## Discussion on Concurrency

In concurrency, we must validate whether multiple users can perform a single action or not. Also, can two threads modify the same resource at the same time? If yes, then it is a critical section and we have a race condition.
Critical sections should be kept as small as possible because while one thread is inside the critical section, others are blocked and cannot proceed.

`Shared Resource -> Critical Section -> Risk -> Solution`

### Step 1 : Find Shared Resources

We must check the shared resources, as that might lead us to the critical section. Long critical sections reduce throughput and increase latency.

Example:

In `BookMyShow` the shared resources are:
1. Seats
2. Shows
3. Bookings

Now, can two users book the same seat simultaneously? If yes, then `Seat` is a shared resource and can end up in a race condition.

### Step 2 : Identify Critical Operations

We would now find the critical operations, as on that basis we can make a decision about which operations need to be atomic.

Example:

[BookMyShow]:

Bad scenario:
1. User A books A1.
2. User B books A1.
3. Both succeed.

This should never happen.
Therefore: Seat booking is critical.


### Step 3 : Protect Shared State

We will check who owns the shared resource and lock the smallest possible resource.

Thus `bookSeat()` should be synchronized/locked.

### Step 4 : Read vs Write

Many systems have:

1. 90% reads
2. 10% writes

Then a Read-Write Lock becomes useful. Many users can read simultaneously. Only writers block each other.


### Lock Granularity

Lock granularity means the amount of data or resources that a lock protects. In other words, it answers the question:

`“How much of the system should be locked while an operation is running?”`

Locks can be `coarse-grained` (covering a large portion of the system) or `fine-grained` (covering a smaller part). Choosing the right lock granularity is important in concurrent systems because it has a direct impact on performance, scalability, and overall efficiency.

If the lock is too large, multiple operations may be blocked even when they don't interfere with each other, reducing concurrency. On the other hand, if locks are too small, the system becomes more complex to manage and may lead to issues such as deadlocks, increased synchronization overhead, and harder maintenance. Therefore, finding a balance between coarse-grained and fine-grained locking is essential for achieving both correctness and good performance.

### Lock contention

Lock contention occurs when multiple threads or processes try to acquire the same lock at the same time. In simple terms, it answers the question:

`“How many operations are competing for the same lock?”`

Lock contention is a common challenge in concurrent systems because only one thread can hold a lock at a time. When several threads need access to the same protected resource, some of them must wait until the lock is released.

The level of contention can be low or high. Low contention means threads rarely wait for each other, allowing the system to run efficiently. High contention means many threads are frequently blocked while waiting for a lock, which can reduce performance, increase response time, and limit scalability.

Managing lock contention is important because excessive contention can create bottlenecks in the system. Common ways to reduce contention include using finer-grained locks, minimizing the time locks are held, partitioning shared data, or using lock-free and concurrent data structures when appropriate.

### Read-Write Locks

A Read-Write Lock (also known as a Reader-Writer Lock) is a synchronization mechanism that improves concurrency when shared data is read much more often than it is modified. Unlike a traditional mutex, which allows only one thread to access a resource at a time, a read-write lock treats read and write operations differently.

Multiple threads can hold a read lock simultaneously because reading does not change the data. However, a thread that wants to modify the data must acquire a write lock, which grants exclusive access to the resource. While a write lock is held, no other readers or writers can access the resource.

The core principle is straightforward:

“Multiple readers can access the resource together, but a writer requires exclusive access.”

This approach significantly improves performance in read-heavy workloads because read operations do not block one another. As a result, the system can handle more concurrent requests, increase throughput, and make better use of available resources while still maintaining data consistency during write operations.


### Optimistic vs Pessimistic Locking

Optimistic locking and pessimistic locking are two strategies used to handle situations where multiple users, threads, or services may try to update the same data at the same time. Their main goal is to maintain data consistency and prevent one user's changes from accidentally overwriting another's.

The key difference lies in how they deal with potential conflicts:

Pessimistic locking assumes conflicts are likely to happen.
Optimistic locking assumes conflicts are uncommon.

Because of this difference, the two approaches behave very differently in terms of performance, scalability, and user experience.

#### Pessimistic Locking

Pessimistic locking follows a cautious approach. It assumes that if multiple users can access the same data, there is a good chance that more than one of them will try to modify it.

To avoid conflicts, the system locks the data as soon as a transaction starts working with it. While the lock is held, other users or transactions must wait until the lock is released before they can make changes.

Think of it like booking a meeting room. Once someone reserves the room, nobody else can use it until that reservation ends. The lock guarantees that no conflicts occur, but it can also cause waiting and reduce concurrency.

The idea is:

"Prevent conflicts before they happen."

#### Optimistic Locking

Optimistic locking takes the opposite approach. Instead of locking data immediately, it allows multiple users to read and modify their own copies of the data simultaneously.

When a user finally tries to save the changes, the system checks whether someone else has modified the same data in the meantime. If no changes were made, the update succeeds. If another user already updated the data, the system detects the conflict and rejects or retries the operation.

A common way to implement this is by using a version number or timestamp. Every update increments the version. Before saving, the application verifies that the version has not changed since the data was read.

The idea is:

"Let everyone work freely and check for conflicts only at the end."