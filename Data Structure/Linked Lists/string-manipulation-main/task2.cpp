//ahmed shawkat eladl:20236006
//khaled mohamed ali:20235010
#include <iostream>

using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node* prev;

    Node(char k) {
        data = k;
        next = prev = nullptr;
    }
};

class StringDLL {
private:
    Node* head;
    Node* tail;

public:
    StringDLL() {
        head = tail = nullptr;
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
    }

    void insertAt(int position, char c) {
        Node* newnode = new Node(c);
        if (position == 0) {
            newnode->next = head;
            if (head != nullptr) {
                head->prev = newnode;
            } else {
                tail = newnode;
            }
            head = newnode;
            return;
        }
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < position - 1; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "wrong position" << endl;
            delete newnode;
            return;
        }
        newnode->next = temp->next;
        newnode->prev = temp;

        if (temp->next != nullptr) {
            temp->next->prev = newnode;
        } else {
            tail = newnode;
        }

        temp->next = newnode;
    }

    void Delete(int position) {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        Node* temp = head;

        if (position == 0) {
            head = head->next;
            if (head != nullptr)
                head->prev = nullptr;
            else
                tail = nullptr;
            delete temp;
            return;
        }

        for (int i = 0; temp != nullptr && i < position; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Invalid position" << endl;
            return;
        }

        if (temp->prev != nullptr)
            temp->prev->next = temp->next;

        if (temp->next != nullptr)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    int stringLength() {
        int count = 0;
        Node* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    void Concatenation(StringDLL& other) {
        Node* temp = other.head;
        while (temp != nullptr) {
            insertAt(stringLength(), temp->data);
            temp = temp->next;
        }
    }

    StringDLL substring(int index, int length) {
        StringDLL result;
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < index; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Start position is invalid" << endl;
            return result;
        }
        for (int i = 0; temp != nullptr && i < length; i++) {
            result.insertAt(result.stringLength(), temp->data);
            temp = temp->next;
        }

        return result;
    }

    void search(StringDLL& substring) {
        if (substring.head == nullptr) {
            cout << "Substring is empty" << endl;
            return;
        }

        Node* currChar = head;
        int currentPosition = 0;
        bool found = false;

        while (currChar != nullptr) {
            Node* subchar = substring.head;
            Node* valChar = currChar;
            bool matching = true;

            while(subchar != nullptr && valChar != nullptr) {
                if (subchar->data != valChar->data) {
                    matching = false;
                    break;
                }
                subchar = subchar->next;
                valChar = valChar->next;
            }

            if (matching && subchar == nullptr) {
                cout << "Substring found starting at position: " << currentPosition << endl;
                found = true;
                return;
            }

            currChar = currChar->next;
            currentPosition++;
        }

        if (!found) {
            cout << "Substring not found" << endl;
        }
    }

    void replacement(StringDLL& Oldsubstring, StringDLL& newsubstring) {
        if (head == nullptr || Oldsubstring.head == nullptr) {
            cout << "Nothing to replace" << endl;
            return;
        }

        Node* current = head;
        int position = 0;

        while (current != nullptr) {
            Node* temp = current;
            Node* temp2 = Oldsubstring.head;
            bool matching = true;

            while (temp != nullptr && temp2 != nullptr) {
                if (temp->data != temp2->data) {
                    matching = false;
                    break;
                }
                temp = temp->next;
                temp2 = temp2->next;
            }

            if (matching && temp2 == nullptr) {
                for (int i = 0; i < Oldsubstring.stringLength(); i++) {
                    Delete(position);
                }

                Node* newNode = newsubstring.head;
                int insertPos = position;
                while (newNode != nullptr) {
                    insertAt(insertPos, newNode->data);
                    newNode = newNode->next;
                    insertPos++;
                }

                current = head;
                for (int i = 0; i < insertPos; i++) {
                    if (current == nullptr) break;
                    current = current->next;
                }
                position = insertPos;
            } else {
                current = current->next;
                position++;
            }
        }
    }
};

int main() {
StringDLL l1,l2;
    string input;
    int length,index;

    cout<<"Enter string to add to l1:";
    cin>>input;
    for (int i=0;i<input.size();i++) {
        l1.insertAt(i,input[i]);
    }
    cout<<"Enter string to add to l2:";
    cin>>input;
    for (int i=0;i<input.size();i++) {
        l2.insertAt(i,input[i]);
    }
    l1.Concatenation(l2);
    cout<<"The concatenation: "<<endl;
    l1.display();

    cout<<"Choose a character by index to remove:";
    cin>>index;
    l1.Delete(index);
    cout<<"The deletion: "<<endl;
    l1.display();


    cout<<"Enter index and length to get substring: ";
    cin>>index>>length;
    StringDLL substring=l1.substring(index,length);
    cout<<"The substring: "<<endl;
    substring.display();

    cout<<"Search for a string in the list: ";
    cin>>input;
    StringDLL search;
    for (int i=0;i<input.size();i++) {
        search.insertAt(i,input[i]);
    }
    l1.search(search);
    cout<<"The search: "<<endl;

    l1.display();

    cout<<"enter substring to replace";
    string oldsubstring,newsubstring;
    cin>>oldsubstring;
    StringDLL oldsubstr;
    for (int i=0;i<oldsubstring.size();i++) {
        oldsubstr.insertAt(i,oldsubstring[i]);
    }
    cout<<"enter replacement substring "<<endl;
    cin>>newsubstring;
    StringDLL newsubstr;
    for (int i=0;i<newsubstring.size();i++) {
        newsubstr.insertAt(i,newsubstring[i]);

    }
   l1.replacement(oldsubstr,newsubstr);
    cout<<"The replacement: "<<endl;
    l1.display();






}