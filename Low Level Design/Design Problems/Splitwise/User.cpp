#include "User.h"
#include "Group.h"

#include <algorithm>

User::User(const string& userId, const string& name, const string& email) : userId(userId), name(name), email(email) {}

void User::joinGroup(Group* group) {

    if(group == nullptr) {

        return;
    }

    auto it = find(groups.begin(), groups.end(), group);

    if(it == groups.end()) {

        groups.push_back(group);
    }
}

void User::leaveGroup(Group* group) {

    auto it = find(groups.begin(), groups.end(), group);

    if(it != groups.end()) {

        groups.erase(it);
    }
}

string User::getUserId() const {

    return userId;
}

string User::getName() const {

    return name;
}

string User::getEmail() const {

    return email;
}

vector<Group*>& User::getGroups() {

    return groups;
}