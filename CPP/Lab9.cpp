#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct nodeDouble {
    double value;
    nodeDouble* next;

    nodeDouble(double val) {value = val;}
};

class queueDouble {
    nodeDouble* head;
    nodeDouble* tail;

    public:
        void enqueue(double val) {
            nodeDouble* newNode = new nodeDouble(val);

            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        double dequeue() {
            if (!head) {
                return 0;
            }

            double value = head->value;

            head = head->next;

            return value;
        }

        double sum() {
            double total = 0;
            nodeDouble* current = head;
            while (current) {
                total += head->value;
                current = current->next;
            }

            return total;
        }
};


struct node {
    string value;
    node* next;

    node(string val) {value = val;}
};

class queue {
    node* head;
    node* tail;


    public:
        void registerPatient(string name) {
            node* newNode = new node(name);

            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        string callPatient() {
            string patientName = head->value;

            head = head->next;

            return patientName;
        }

        void displayQueue() {
            node* current = head;
            while (current) {
                cout << current->value << ", ";
                current = current->next;
            }
        }
};

int main() {
    queueDouble Q1;
    queueDouble Q2;
    queueDouble Q3;

    Q1.enqueue(34.5);
    Q1.enqueue(22.5);
    Q1.enqueue(44.5);
    Q2.enqueue(10.4);
    Q2.enqueue(35.7);
    Q2.enqueue(38.7);
    Q2.enqueue(19.7);
    Q3.enqueue(Q2.dequeue());
    Q3.enqueue(Q2.dequeue());
    Q3.enqueue(Q1.dequeue());
    Q2.enqueue(66.7);

    cout << Q1.sum() << ", " << Q2.sum() << ", " << Q3.sum() << ", " << endl;

    queue clinicQueue;

    clinicQueue.registerPatient("adam");
    clinicQueue.registerPatient("ava");
    clinicQueue.registerPatient("amar");
    clinicQueue.registerPatient("aeir");
    clinicQueue.registerPatient("aex");

    cout << clinicQueue.callPatient() << endl;
    clinicQueue.displayQueue();


}