#include <iostream>
#include <string>
#include "BST.h"
using namespace std;
#ifndef HEAP_H
#define HEAP_H

class Heap {
private:
    TaskObject heap[500];
    int size = 0;

public:
    void buildHeap(TaskObject arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
    }

    void heapify(TaskObject arr[], int n, int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int min = i;
        if (l < n && arr[l].task_duration < arr[min].task_duration) min = l;
        if (r < n && arr[r].task_duration < arr[min].task_duration) min = r;
        if (min != i) {
            swap(arr[i], arr[min]);
            heapify(arr, n, min);
        }
    }

    void mark_as_completed(TreeNode* node, TaskBST& tree, int duration, string desc) {

        TaskObject matched[100];
        int count = 0;
        findMatchingTasks(node, duration, matched, count);


        cout << "//" << count << " tasks are found" << endl;
        for (int i = 0; i < count; i++) {
            cout << "[" << matched[i].task_name << ", " << matched[i].task_duration << ", " << matched[i].task_category << "]" << endl;
        }


        cout << "Task duration: " << duration << endl;
        cout << "Task description: " << desc << endl;


        string descLower = desc;
        for (char& c : descLower) c = tolower(c);


        TaskObject* foundTask = nullptr;
        for (int i = 0; i < count; i++) {
            string taskNameLower = matched[i].task_name;
            for (char& c : taskNameLower) c = tolower(c);

            if (taskNameLower.find(descLower) != string::npos) {
                foundTask = &matched[i];
                break;
            }
        }

        if (foundTask) {

            bool taskRemoved = removeSpecificTask(tree.root, *foundTask, tree);

            if (taskRemoved) {

                heap[size] = *foundTask;
                int pos = size++;
                while (pos > 0 && heap[(pos - 1) / 2].task_duration > heap[pos].task_duration) {
                    swap(heap[pos], heap[(pos - 1) / 2]);
                    pos = (pos - 1) / 2;
                }

                cout << "[" << foundTask->task_name << ", " << foundTask->task_duration << ", " << foundTask->task_category << "]" << endl;
                cout << "This task is removed" << endl;


                int otherCount = count - 1;
                if (otherCount > 0) {
                    cout << "//choose to complete other " << otherCount << " tasks (duration = ";
                    bool first = true;
                    for (int i = 0; i < count; i++) {
                        if (matched[i].task_name != foundTask->task_name) {
                            if (!first) cout << ",";
                            cout << matched[i].task_duration;
                            first = false;
                        }
                    }
                    cout << ")" << endl;
                }
            }
        } else {
            cout << "No matching task found with that description." << endl;
        }
    }

    void findMatchingTasks(TreeNode* node, int duration, TaskObject* matched, int& count) {
        if (node == nullptr) return;

        findMatchingTasks(node->left, duration, matched, count);
        if (node->task.task_duration == duration) {
            matched[count++] = node->task;
        }
        findMatchingTasks(node->right, duration, matched, count);
    }

    bool removeSpecificTask(TreeNode*& node, TaskObject& task, TaskBST& tree) {
        if (node == nullptr) return false;


        if (node->task.task_name == task.task_name &&
            node->task.task_duration == task.task_duration &&
            node->task.task_category == task.task_category) {


            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
                return true;
            }

            else if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
                return true;
            }

            else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
                return true;
            }

            else {

                TreeNode* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }


                node->task = successor->task;


                return removeSpecificTask(node->right, successor->task, tree);
            }
        }


        if (removeSpecificTask(node->left, task, tree)) return true;


        return removeSpecificTask(node->right, task, tree);
    }

    void displayCompletedTasks() {
        if (size == 0) {
            cout << "//min heap tree is printed" << endl;
            cout << "No completed tasks." << endl;
            return;
        }

        TaskObject tempHeap[100];
        for (int i = 0; i < size; i++) tempHeap[i] = heap[i];
        int tempSize = size;


        const string allCategories[] = {"Educational", "Health", "Self development", "Food", "Other"};
        const int numCategories = 5;
        int catCount[numCategories] = {0};

        cout << "//min heap tree is printed" << endl;
        while (tempSize > 0) {
            TaskObject minTask = tempHeap[0];
            cout << "[" << minTask.task_name << ", " << minTask.task_duration << ", " << minTask.task_category << "]" << endl;


            for (int i = 0; i < numCategories; i++) {
                if (allCategories[i] == minTask.task_category) {
                    catCount[i]++;
                    break;
                }
            }


            tempHeap[0] = tempHeap[tempSize - 1];
            tempSize--;

            int i = 0;
            while (true) {
                int l = 2 * i + 1;
                int r = 2 * i + 2;
                int minIndex = i;

                if (l < tempSize && tempHeap[l].task_duration < tempHeap[minIndex].task_duration)
                    minIndex = l;
                if (r < tempSize && tempHeap[r].task_duration < tempHeap[minIndex].task_duration)
                    minIndex = r;

                if (minIndex != i) {
                    TaskObject temp = tempHeap[i];
                    tempHeap[i] = tempHeap[minIndex];
                    tempHeap[minIndex] = temp;
                    i = minIndex;
                } else {
                    break;
                }
            }
        }

        cout << "//Category report" << endl;
        for (int i = 0; i < numCategories; i++) {
            cout << allCategories[i] << " = " << catCount[i] << endl;
        }
    }
};

#endif //HEAP_H