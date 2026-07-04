# Overview

The State Design Pattern is a behavioral design pattern used when an object behaves differently depending on its current state, and that behavior keeps changing during its lifetime. Without this we usually write `if-else` or `switch` statements that check the current state before deciding what action to perform.

The State Pattern moves the behavior of each state into its own class.

Suppose an object can be in `State A`, `State B`, or `State C`. Different operations behave differently depending on the current state.

Without the State Pattern, the class usually looks like this:
```cpp []
enum State
{
    A,
    B,
    C
};

void operation1() {

    if(state == A) {

    }
    else if(state == B) {

    }
}
```

If we have multiple states and multiple operations, then we have to write `if-else` or `switch` in every operation for every state.

Problem it creates:

1. Huge `if-else` chains
2. Code duplication
3. Violates `Open-Closed` principle

In State pattern instead of `if(state == A)` we just perform `currentState -> operation(this)` inside the main object. Here each State has its own behavior. The State pattern moves both data and behavior together.

## Components of State Pattern:

#### Context

It is the main object used by the client.
It is responsible for storing current state, changing the current state and delegates the behaviour to current state.

#### State Interface

This defines the common functions every state must implement.

#### Concrete States

Each concrete state implements its own behavior.


Example: Document Management

A document supports operations:
```cpp []
edit()
submitForReview()
approve()
publish()
reject()
```

Now, for a given state we may encounter
```cpp []
void Document::approve() {

    if(state == DRAFT) {

        cout << "Invalid";
    }
    else if(state == REVIEW) {

        cout << "Approved";
        state = APPROVED;
    }
    else if(state == APPROVED) {

        cout << "Already approved";
    }
    else {

        cout << "Already published";
    }
}
```