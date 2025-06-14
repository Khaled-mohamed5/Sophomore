#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
#include "heap.h"

using namespace std;


void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {

    TaskBST bst;
    Heap heap;


    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    int numTasks;
    inputFile >> numTasks;
    inputFile.ignore();


    for (int i = 0; i < numTasks; i++) {
        string description, category;
        int duration;

        getline(inputFile, description);
        inputFile >> duration;
        inputFile.ignore();
        getline(inputFile, category);

        TaskObject task(description, duration, category);
        bst.insert(task);
    }

    inputFile.close();


    int option = 0;
    while (option != 9) {
        cout << "\nMenu:" << endl;
        cout << "1. Insert a task (using BST Class)" << endl;
        cout << "2. Display all (using BST Class)" << endl;
        cout << "3. Search for a task (using BST Class)" << endl;
        cout << "4. Remove a task (using BST Class)" << endl;
        cout << "5. Display more than (using BST Class)" << endl;
        cout << "6. Display less than (using BST Class)" << endl;
        cout << "7. Mark a task as completed by task duration and description (using heap Class)" << endl;
        cout << "8. Display all completed tasks and the number of tasks completed per category (using heap Class)" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter number of option: ";


        if (!(cin >> option)) {
            cout << "Invalid input. Please enter a number." << endl;
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (option == 9) {
            break;
        }

        switch (option) {
            case 1: {
                string description, category;
                int duration;

                cout << "Enter tasks description: ";
                getline(cin, description);

                cout << "Enter duration: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();

                cout << "Enter Category: ";
                getline(cin, category);

                TaskObject task(description, duration, category);
                bst.insert(task);
                break;
            }
            case 2: { // Display all
                bst.displayAll();
                break;
            }
            case 3: { // Search for a task
                int duration;
                cout << "Enter the duration: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
                bst.Search(duration);
                break;
            }
            case 4: { // Remove a task
                int duration;
                cout << "Enter the duration: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
                bst.remove(duration);
                break;
            }
            case 5: { // Display more than
                int duration;
                cout << "Enter the duration more than: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
                bst.SearchGreaterThan(duration);
                break;
            }
            case 6: { // Display less than
                int duration;
                cout << "Enter the duration less than: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
                bst.SearchLessThan(duration);
                break;
            }
            case 7: { // Mark a task as completed
                int duration;
                string description;

                cout << "Task duration: ";
                if (!(cin >> duration)) {
                    cout << "Invalid duration input. Returning to menu." << endl;
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();

                cout << "Task description: ";
                getline(cin, description);

                heap.mark_as_completed(bst.root, bst, duration, description);
                break;
            }
            case 8: { // Display completed tasks
                heap.displayCompletedTasks();
                break;
            }
            default:
                cout << "Invalid option. Please enter a number between 1 and 9." << endl;
        }
    }

    return 0;
}