#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;
class TaskObject {
public:
    string task_name;
    int task_duration;
    string task_category;

    TaskObject() {}

    TaskObject(string tn, int td, string tc) {
        task_name = tn;
        task_duration = td;
        task_category = tc;
    }
};

class TreeNode {
public:
    TaskObject task;
    TreeNode* left;
    TreeNode* right;

    TreeNode(TaskObject t):task(t) {
        left = right = nullptr;
    }
};

class TaskBST {
public:
    TreeNode* root;

    TaskBST() {
        root = nullptr;
    }

    void insert(TaskObject task) {
        if (root == nullptr) {
            root = new TreeNode(task);
        } else {
            TreeNode* current = root;
            while (true) {
                if (task.task_duration <= current->task.task_duration) {
                    if (current->left == nullptr) {
                        current->left = new TreeNode(task);
                        break;
                    }
                    current = current->left;
                } else {
                    if (current->right == nullptr) {
                        current->right = new TreeNode(task);
                        break;
                    }
                    current = current->right;
                }
            }
        }
        cout << "The task is added." << endl;
    }

    void inOrderHelper(TreeNode* task, int& count) {
        if (task == nullptr) return;
        inOrderHelper(task->left, count);
        cout << "[" << task->task.task_name << ", " << task->task.task_duration << ", " << task->task.task_category << "]" << endl;
        count++;
        inOrderHelper(task->right, count);
    }

    void displayAll() {
        int count = 0;
        inOrderHelper(root, count);
        cout << "//" << count << " tasks are printed" << endl;
    }

    void Search(int duration) {
        int count = 0;
        searchByDuration(root, duration,count);
        if (count ==1) {
            cout << "//" << count << " task is found" << endl;
        }
        else if (count >1) {
            cout << "//" << count << " tasks are found" << endl;
        }
        else {
            cout << "//" << count << " task is not found" << endl;
        }
    }

    void searchByDuration(TreeNode* task,int duration, int& count) {
        if (task == nullptr) return;
        searchByDuration(task->left, duration, count);
        if (task->task.task_duration == duration) {
            cout << "[" << task->task.task_name << ", "
            << task->task.task_category << ", "
            << task->task.task_duration << "]" << endl;
            count++;
        }
        searchByDuration(task->right, duration, count);
    }

    void remove(int duration) {
        int removedCount = 0;
        root = remove_task(root, duration, removedCount);
        cout << "//" << removedCount << " tasks are removed" << endl;
    }

    TreeNode* remove_task(TreeNode* task, int duration, int& removedCount) {
        if (task == nullptr) return nullptr;

        task->left = remove_task(task->left, duration, removedCount);
        task->right = remove_task(task->right, duration, removedCount);

        if (task->task.task_duration == duration) {
            removedCount++;
            if (task->left == nullptr && task->right == nullptr) {
                delete task;
                return nullptr;
            } else if (task->left == nullptr) {
                TreeNode* temp = task->right;
                delete task;
                return temp;
            } else if (task->right == nullptr) {
                TreeNode* temp = task->left;
                delete task;
                return temp;
            } else {
                TreeNode* successor = task->right;
                while (successor->left != nullptr)
                    successor = successor->left;
                task->task = successor->task;
                task->right = remove_task(task->right, successor->task.task_duration, removedCount);
            }
        }
        return task;
    }
    void SearchGreaterThan(int duration) {
        int count = 0;
        searchByDurationGT(root, duration,count);
        if (count ==1) {
            cout << "//" << count << " task is found" << endl;
        }
        else if (count >1) {
            cout << "//" << count << " tasks are found" << endl;
        }
        else {
            cout << "//" << count << " task is not found" << endl;
        }
    }

    void searchByDurationGT(TreeNode* task,int duration, int& count) {
        if (task == nullptr) return;
        searchByDurationGT(task->left, duration, count);
        if (task->task.task_duration >= duration) {
            cout << "[" << task->task.task_name << ", "
            << task->task.task_category << ", "
            << task->task.task_duration << "]" << endl;
            count++;
        }
        searchByDurationGT(task->right, duration, count);
    }

    void SearchLessThan(int duration) {
        int count = 0;
        searchByDurationLT(root, duration,count);
        if (count ==1) {
            cout << "//" << count << " task is found" << endl;
        }
        else if (count >1) {
            cout << "//" << count << " tasks are found" << endl;
        }
        else {
            cout << "//" << count << " task is not found" << endl;
        }
    }

    void searchByDurationLT(TreeNode* task,int duration, int& count) {
        if (task == nullptr) return;
        searchByDurationLT(task->left, duration, count);
        if (task->task.task_duration <= duration) {
            cout << "[" << task->task.task_name << ", "
            << task->task.task_category << ", "
            << task->task.task_duration << "]" << endl;
            count++;
        }
        searchByDurationLT(task->right, duration, count);
    }
};

#endif //BST_H
