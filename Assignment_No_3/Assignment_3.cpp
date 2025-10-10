#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Knowledge base using maps                 
map<string, vector<string>> parentToChildren; // Parent → list of children
map<string, string> childToParent;            // Child → parent

// Function to add a relationship to knowledge base   
void addRelation(string parent, string child) {
    parentToChildren[parent].push_back(child); // Add child under parent              
    childToParent[child] = parent;             // Store parent of the child
}

// Function to display children of a given person
void showChildren(string parent) {
    if (parentToChildren.find(parent) != parentToChildren.end()) {
        cout << "Children of " << parent << ": ";
        for (string child : parentToChildren[parent]) {
            cout << child << " ";
        }
        cout << endl;
    } else {
        cout << parent << " has no recorded children in the knowledge base.\n";
    }
}

// Function to display parent of a given person
void showParent(string child) {
    if (childToParent.find(child) != childToParent.end()) {
        cout << "Parent of " << child << " is " << childToParent[child] << endl;
    } else {
        cout << "Parent of " << child << " not found in the knowledge base.\n";
    }
}
                         
// Menu-driven main program
int main() {
    int choice;
    string parent, child, name;

    cout << "===== Family Tree Parser Using Knowledge Base =====\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add parent-child relation\n";    
        cout << "2. Show children of a person\n";
        cout << "3. Show parent of a person\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter parent name: ";
            cin >> parent;
            cout << "Enter child name: ";
            cin >> child;
            addRelation(parent, child);
            cout << "Relation added!\n";
            break;

        case 2:
            cout << "Enter name to find children: ";
            cin >> name;
            showChildren(name);
            break;

        case 3:
            cout << "Enter name to find parent: ";
            cin >> name;
            showParent(name);
            break;

        case 4:
            cout << "Exiting program. Thank you!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
