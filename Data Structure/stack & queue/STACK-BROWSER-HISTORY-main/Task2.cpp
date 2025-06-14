#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    string url;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(string url) {
        Node* newNode = new Node{url, top};
        top = newNode;
    }

    string pop() {
        if (!top) return "";
        Node* temp = top;
        string url = top->url;
        top = top->next;
        delete temp;
        return url;
    }

    string peek() {
        return top ? top->url : "";
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

string getOrdinal(int i) {
    switch (i) {
        case 1: return "First";
        case 2: return "Second";
        case 3: return "Third";
        case 4: return "Fourth";
        case 5: return "Fifth";
        case 6: return "Sixth";
        case 7: return "Seventh";
        case 8: return "Eighth";
        case 9: return "Ninth";
        case 10: return "Tenth";
        default: return to_string(i);
    }
}

int main() {
    Stack backStack, forwardStack;
    string urls[9], actions[10];
    string current;

    ifstream file("URLs.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open URLs.txt\n";
        return 1;
    }

    for (int i = 0; i < 9; i++) {
        getline(file, urls[i]);
    }

    for (int i = 0; i < 10; i++) {
        file >> actions[i];
    }


    for (int i = 0; i < 8; i++) {
        backStack.push(urls[i]);
    }
    current = urls[8];


    cout << "The current page is:\n" << current << "\n";


    for (int i = 0; i < 10; i++) {
        cout << getOrdinal(i + 1) << " Choice [" << actions[i] << "]\n";

        if (actions[i] == "Backward" && !backStack.isEmpty()) {
            forwardStack.push(current);
            current = backStack.pop();
        } else if (actions[i] == "Forward" && !forwardStack.isEmpty()) {
            backStack.push(current);
            current = forwardStack.pop();
        }

        cout << "The current page is:\n" << current << "\n";

        cout << "The Next one is:\n";
        if (!forwardStack.isEmpty())
            cout << forwardStack.peek() << "\n";
        else
            cout << "None\n";

        cout << "The Previous one is:\n";
        if (!backStack.isEmpty())
            cout << backStack.peek() << "\n";
        else
            cout << "None\n";

        cout << "---------------------------------------------------\n";
    }

    return 0;
}
