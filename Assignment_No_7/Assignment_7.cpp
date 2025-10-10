#include <bits/stdc++.h>
using namespace std;

struct Rule {
    vector<string> premises; // IF part
    string conclusion;       // THEN part
};

class ForwardChaining {  
    vector<Rule> rules;
    set<string> facts;   // known facts         
    string goal;

public:
    void addRule() {
        int n;
        cout << "Enter number of premises: ";
        cin >> n;

        Rule r;
        cout << "Enter premises:\n";
        for (int i = 0; i < n; i++) {
            string p;
            cin >> p;
            r.premises.push_back(p);
        }

        cout << "Enter conclusion: ";
        cin >> r.conclusion;

        rules.push_back(r);
        cout << "Rule added successfully!\n";
    }

    void addFact() {
        string f;
        cout << "Enter fact: ";
        cin >> f;
        facts.insert(f);
        cout << "Fact added successfully!\n";
    }

    void setGoal() {
        cout << "Enter goal: ";
        cin >> goal;
    }

    void display() {
        cout << "\n--- Rules ---\n";
        for (int i = 0; i < rules.size(); i++) {
            cout << "R" << i + 1 << ": ";
            for (int j = 0; j < rules[i].premises.size(); j++) {
                cout << rules[i].premises[j];
                if (j != rules[i].premises.size() - 1) cout << " AND ";
            }
            cout << " -> " << rules[i].conclusion << "\n";
        }

        cout << "\n--- Facts ---\n";
        for (auto &f : facts) cout << f << " ";
        cout << "\nGoal: " << goal << "\n";
    }

    void forwardChaining() {
        cout << "\nApplying Forward Chaining...\n";

        bool newFactAdded = true;
        set<string> derivedFacts = facts;

        while (newFactAdded) {
            newFactAdded = false;

            for (auto &r : rules) {
                bool allPremisesTrue = true;

                for (auto &p : r.premises) {
                    if (derivedFacts.find(p) == derivedFacts.end()) {
                        allPremisesTrue = false;
                        break;
                    }
                }

                if (allPremisesTrue && derivedFacts.find(r.conclusion) == derivedFacts.end()) {
                    cout << "Derived new fact: " << r.conclusion << "\n";
                    derivedFacts.insert(r.conclusion);
                    newFactAdded = true;
                }

                if (derivedFacts.find(goal) != derivedFacts.end()) {
                    cout << "\n✅ Goal '" << goal << "' is reached!\n";
                    return;
                }
            }
        }

        cout << "\n❌ Goal '" << goal << "' cannot be derived.\n";
    }
};

int main() {
    ForwardChaining fc;
    int choice;

    do {
        cout << "\n--- Forward Chaining Menu ---\n";
        cout << "1. Add Rule\n";
        cout << "2. Add Fact\n";
        cout << "3. Set Goal\n";
        cout << "4. Display Knowledge Base\n";
        cout << "5. Apply Forward Chaining\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fc.addRule(); break;
            case 2: fc.addFact(); break;
            case 3: fc.setGoal(); break;
            case 4: fc.display(); break;
            case 5: fc.forwardChaining(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
    