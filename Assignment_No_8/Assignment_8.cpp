#include <bits/stdc++.h>
using namespace std;

// Knowledge Base: Rules stored as {conclusion : {premises}}
map<string, vector<vector<string>>> rules;
// Facts in knowledge base
set<string> facts;

// Function to check if a goal can be proven using backward chaining
bool backwardChaining(string goal, set<string> &visited) {
    // If goal is already a known fact
    if (facts.find(goal) != facts.end())
        return true;

    // To avoid infinite loops in recursive calls
    if (visited.find(goal) != visited.end())
        return false;
    visited.insert(goal);

    // If rules exist that can conclude the goal
    if (rules.find(goal) != rules.end()) {                                  
        for (auto premises : rules[goal]) {
            bool allTrue = true;
            for (auto p : premises) {
                if (!backwardChaining(p, visited)) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue)
                return true;
        }
    }
    return false;
}

int main() {
    int choice;
    string goal;

    // Sample Knowledge Base
    // Rule: If "A" and "B" then "C"
    rules["C"].push_back({"A", "B"});
    // Rule: If "D" then "B"
    rules["B"].push_back({"D"});
    // Facts
    facts.insert("A");
    facts.insert("D");

    do {
        cout << "\n=== Backward Chaining Menu ===\n";
        cout << "1. Show Knowledge Base\n";
        cout << "2. Query (Check if a fact can be proven)\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nFacts: ";
            for (auto f : facts) cout << f << " ";
            cout << "\nRules:\n";
            for (auto r : rules) {
                for (auto premises : r.second) {
                    cout << "IF ";
                    for (int i = 0; i < premises.size(); i++) {
                        cout << premises[i];
                        if (i != premises.size() - 1) cout << " AND ";
                    }
                    cout << " THEN " << r.first << "\n";
                }
            }
            break;

        case 2:
            cout << "Enter goal to prove: ";
            cin >> goal;
            {
                set<string> visited;
                if (backwardChaining(goal, visited))
                    cout << "Goal '" << goal << "' can be PROVEN.\n";
                else
                    cout << "Goal '" << goal << "' CANNOT be proven.\n";
            }
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);
                                                    
    return 0;
}
        


