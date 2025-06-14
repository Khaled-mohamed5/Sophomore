#include <iostream>
#include <fstream>
using namespace std;

class Queue {
private:
    struct Node {
        string pcName;
        string arriveTime;
        int duration;
        int execTime;
        int waitTime;
        Node* next;

        Node(string name, string time, int dur)
            : pcName(name), arriveTime(time), duration(dur),
              next(nullptr), execTime(0), waitTime(0) {}
    };

    int length;
    Node* front;
    Node* rear;

public:
    Queue() : length(0), front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return (length == 0);
    }

    void enqueue(string pcName, string arriveTime, int duration) {
        Node* newNode = new Node(pcName, arriveTime, duration);

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        length++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        length--;
        if (isEmpty()) {
            rear = nullptr;
        }
    }

    Node* getFront() const {
        return front;
    }

    int convToMin(string arriveTime) {
        int hours = stoi(arriveTime.substr(0, 2));
        int minutes = stoi(arriveTime.substr(3, 2));
        return hours * 60 + minutes;
    }

    void sortJobs() {
        if (isEmpty() || front->next == nullptr) return;

        for (Node*i = front; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                int timeI = convToMin(i->arriveTime);
                int timeJ = convToMin(j->arriveTime);

                if (timeI > timeJ || (timeI == timeJ && i->duration > j->duration)) {
                    swap(i->pcName, j->pcName);
                    swap(i->arriveTime, j->arriveTime);
                    swap(i->duration, j->duration);
                }
            }
        }
    }


    void jobsExecution() {
        int currentTime = 0;
        int totalOccupiedTime = 0;
        int totalWaitTime = 0;
        int executedJobs = 0;

        cout << "Jobs execution:\n";
        while (!isEmpty()) {
            Node* job = getFront();
            int arrived = convToMin(job->arriveTime);

            if (currentTime < arrived) {
                currentTime = arrived;
            }

            job->execTime = currentTime;
            job->waitTime = currentTime - arrived;

            cout << job->pcName << " " << job->arriveTime << " " << job->duration
                 << " executed at " << job->execTime << " waiting time: " << job->waitTime << endl;

            currentTime += job->duration;
            totalOccupiedTime += job->duration;
            totalWaitTime += job->waitTime;
            executedJobs++;

            dequeue();
        }

        cout << "The printer was occupied for " << totalOccupiedTime << " minutes" << endl;
        if (executedJobs > 0) {
            float average = float(totalWaitTime) / float(executedJobs);
            cout << "Average waiting time for all jobs is: " << average << endl;
        }
    }
};

int main() {
    Queue q;
    ifstream file("printer.txt");

    if (!file) {
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    int jobs;
    file >> jobs;

    for (int i = 0; i < jobs; ++i) {
        string pc, time;
        int duration;

        file >> pc >> time >> duration;
        q.enqueue(pc, time, duration);
    }
    file.close();

    q.sortJobs();
    q.jobsExecution();

    return 0;
}



