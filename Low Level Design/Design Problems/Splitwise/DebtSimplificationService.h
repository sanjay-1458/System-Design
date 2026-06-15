#ifndef DEBT_SIMPLIFICATION_SERVICE_H
#define DEBT_SIMPLIFICATION_SERVICE_H

#include <unordered_map>
#include <vector>

using namespace std;

class User;
class Group;
class Settlement;

class DebtSimplificationService {

public:

    unordered_map<User*, double> calculateNetBalances(Group* group);

    vector<Settlement*> simplifyDebts(Group* group);

private:

    vector<Settlement*> backtrackingSimplification(unordered_map<User*, double>& balances);

    void dfs(vector<pair<User*, double>>& debts, int start, vector<Settlement*>& current, vector<Settlement*>& best);
};

#endif