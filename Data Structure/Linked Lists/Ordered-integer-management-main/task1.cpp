//ahmed shawkat eladl:20236006
//khaled mohamed ali:20235010


#include <iostream>
using namespace std;

class Node
{
public:
    int info;
    Node* next;
    int ctr;
    Node(int i, Node* n = nullptr)
    {
        info = i;
        next = n;
        ctr = 1;
    }
};

void addInOrder(int info, Node*& head) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr && temp->info < info) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr && temp->info == info) {
        temp->ctr++;
    }
    else {
        Node* newNode = new Node(info);


        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {

            newNode->next = prev->next;
            prev->next = newNode;
        }
    }
}
void deleteValue(int val, Node*& head) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->info == val) {
            if (temp->ctr > 1) {
                temp->ctr--;
            } else {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
                continue;
            }
        }
        prev = temp;
        temp = temp->next;
    }
}

void removeMax(Node* &head) {
    if (head == nullptr) {
        cout << "Empty list" << endl;
        return;
    }

    // Find the maximum value
    int max = head->info;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->info > max) {
            max = temp->info;
        }
        temp = temp->next;
    }

    bool maxExists;
    do {
        maxExists = false;
        temp = head;
        while (temp != nullptr) {
            if (temp->info == max) {
                maxExists = true;
                break;
            }
            temp = temp->next;
        }
        if (maxExists) {
            deleteValue(max, head);
        }
    } while (maxExists);
}



void display(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        for (int i = 0; i < temp->ctr; i++) {
            cout << temp->info << " ";
        }
        temp = temp->next;
    }
    cout << endl;
}
void displayDescending(Node* head) {
    if (head == nullptr) {
        cout<<"Empty list"<<endl;
    }
    int max=head->info;
    int min=head->info;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->info > max) {
            max = temp->info;
        }
        if (temp->info < min) {
            min = temp->info;
        }
        temp=temp->next;

    }
    for (int val=max;val>=min;--val) {
        temp=head;
        while (temp != nullptr) {
            if (temp->info == val) {
                for (int i=0;i<temp->ctr;++i) {
                    cout<<val<<" ";
                }
                break;
            }
            temp = temp->next;
        }
    }
    cout<<endl;
}
void generateFromArray(int arr[],int size,Node*& head) {
    for(int i=0;i<size;++i){
        addInOrder(arr[i],head);
    }
}
void clear(Node*& head){
    Node* temp=head;
    while(head!=nullptr){
        temp=head;
        head=head->next;
        delete temp;
    }

}
int main() {
    Node* head = nullptr;
    int choice, value;
    int arr[100];
    int size;

    do {
        cout << "\n 1.Add 2.Del 3.removeMax 4.display 5.display descending 6.Array 7.Clear 8.Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Add value: ";
            cin >> value;
            addInOrder(value, head);
            break;

            case 2:
                if (!head) cout << "Empty!\n";
                else {
                    cout << "Del value: ";
                    cin >> value;
                    deleteValue(value, head);
                }
            break;

            case 3:
                if (!head) cout << "Empty!\n";
                else removeMax(head);
            break;

            case 4:
                if (!head) cout << "Empty!\n";
                else display(head);
            break;

            case 5:
                if (!head) cout << "Empty!\n";
                else displayDescending(head);
            break;

            case 6:
                cout << "Array size: ";
            cin >> size;
            cout << "Elements: ";
            for (int i = 0; i < size; i++) cin >> arr[i];
            generateFromArray(arr, size, head);
            break;

            case 7:
                clear(head);
            cout << "Cleared\n";
            break;

            case 8:
                cout << "Exiting\n";
            break;

            default:
                cout << "Invalid!\n";
        }
    } while (choice != 8);

    clear(head);
    return 0;
}