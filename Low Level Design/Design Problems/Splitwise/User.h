#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class Group;

class User {

private:

    string userId;
    string name;
    string email;
    vector<Group*> groups;

public:

    User(const string& userId, const string& name, const string& email);

    void joinGroup(Group* group);
    void leaveGroup(Group* group);

    string getUserId() const;
    string getName() const;
    string getEmail() const;

    vector<Group*>& getGroups();
};

#endif