#include "DebtSimplificationService.h"

#include "Group.h"
#include "Expense.h"
#include "ExpenseSplit.h"
#include "Settlement.h"
#include "User.h"

#include <cmath>

using namespace std;

unordered_map<User*, double> DebtSimplificationService::calculateNetBalances(Group* group) {

    unordered_map<User*, double> balances;

    for(User* user: group -> getMembers()) {

        balances[user] = 0.0;
    }

    for(Expense* expense: group -> getExpenses()) {

        if(expense -> getIsDeleted()) {

            continue;
        }

        User* payer = expense -> getPaidBy();

        balances[payer] += expense -> getAmount();

        for(ExpenseSplit* split: expense -> getSplits()) {

            balances[split -> getUser()] -= split -> getShareAmount();
        }
    }

    for(Settlement* settlement: group -> getSettlements()) {

        balances[settlement -> getPayer()] += settlement -> getAmount();

        balances[settlement -> getReceiver()] -= settlement -> getAmount();
    }

    return balances;
}

vector<Settlement*> DebtSimplificationService::simplifyDebts(Group* group) {

    auto balances = calculateNetBalances(group);

    return backtrackingSimplification(balances);
}

vector<Settlement*> DebtSimplificationService::backtrackingSimplification(unordered_map<User*, double>& balances) {

    vector<pair<User*, double>> debts;

    for(auto& entry: balances) {

        if(fabs(entry.second) > 0.0001) {

            debts.push_back({entry.first, entry.second});
        }
    }

    vector<Settlement*> current;
    vector<Settlement*> best;

    dfs(debts, 0, current, best);

    return best;
}

void DebtSimplificationService::dfs(vector<pair<User*, double>>& debts, int start, vector<Settlement*>& current, vector<Settlement*>& best) {

    while(start < debts.size() && fabs(debts[start].second) < 0.0001) {

        start++;
    }

    if(start == debts.size()) {

        if(best.empty() || current.size() < best.size()) {

            best.clear();

            for(Settlement* settlement: current) {

                best.push_back(new Settlement(settlement -> getSettlementId(), settlement -> getPayer(), settlement -> getReceiver(), settlement -> getAmount()));
            }
        }

        return;
    }

    for(int i = start + 1; i < debts.size(); ++i) {

        if(debts[start].second * debts[i].second >= 0) {

            continue;
        }

        double original = debts[i].second;

        double amount = min(fabs(debts[start].second), fabs(debts[i].second));

        Settlement* settlement;

        if(debts[start].second < 0) {

            settlement = new Settlement("AUTO", debts[start].first, debts[i].first, amount);
        }
        else {

            settlement = new Settlement("AUTO", debts[i].first, debts[start].first, amount);
        }

        current.push_back(settlement);

        debts[i].second += debts[start].second;

        dfs(debts, start + 1, current, best);

        debts[i].second = original;

        delete current.back();

        current.pop_back();

        if(fabs(original + debts[start].second) < 0.0001) {

            break;
        }
    }
}