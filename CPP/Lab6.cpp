#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct linkedList {
    int studentID;
    string studentName;
    int studentAge;
    linkedList* next;
};

linkedList* insertHead(int studentID, int studentAge, string studentName, linkedList* list) {
    linkedList* head = new linkedList();

    head->studentID = studentID;
    head->studentAge = studentAge;
    head->studentName = studentName;
    head->next = list;

    return head;
}

void printLinkedList(linkedList* list) {
    while (true) {
        cout << list->studentID << " " << list->studentName << " " << list->studentAge << ", ";

        if (list->next == nullptr) {
            break;
        }

        list = list->next;
        cout << endl;
    }

    cout << endl;
}

linkedList* insertEnd(int studentID, int studentAge, string studentName, linkedList* list) {
    linkedList* head = list;

    while (true) {
        if (list->next == nullptr) {
            break;
        }

        list = list->next;
    }

    list->next = new linkedList();
    list->next->studentID = studentID;
    list->next->studentAge = studentAge;
    list->next->studentName = studentName;

    return head;
}

struct songLinkedList {
    int id;
    string artistName;
    string songName;
    int releaseYear;
    string genre;
    float length;
    songLinkedList* next;
};

songLinkedList* insertHead(int id, string artistName, string songName, int releaseYear, 
    string genre, float length, songLinkedList* list) {
    songLinkedList* head = new songLinkedList();

    head->id = id;
    head->artistName = artistName;
    head->songName = songName;
    head->genre = genre;
    head->length = length;
    head->next = list;

    return head;
}

void printLinkedList(songLinkedList* list) {
    while (true) {
        cout << list->id << " " << list->artistName << " " << 
        list->songName << " " << list->genre << " " << list->length << ", ";

        if (list->next == nullptr) {
            break;
        }

        list = list->next;
        cout << endl;
    }

    cout << endl;
}

songLinkedList* insertEnd(int id, string artistName, string songName, int releaseYear, 
    string genre, float length, songLinkedList* list) {
    songLinkedList* head = list;

    songLinkedList* node = new songLinkedList();
    node->id = id;
    node->artistName = artistName;
    node->songName = songName;
    node->genre = genre;
    node->length = length;
    node->next = nullptr;

    while (true) {
        if (list->next == nullptr) {
            break;
        }

        list = list->next;
    }

    list->next = node;

    return head;
}

int main() {
    linkedList* a = new linkedList();

    a->studentID = 1;
    a->studentAge = 10;
    a->studentName = "aben";
    a->next = nullptr;

    cout << a->studentID;

    linkedList* newListHead = insertHead(10, 10, "erab", a);
    printLinkedList(newListHead);

    linkedList* newListEnd = insertEnd(20, 20, "manon", newListHead);
    printLinkedList(newListEnd);

    songLinkedList* b = new songLinkedList();

    b->id = 1;
    b->artistName = "Celine Dion";
    b->songName = "Just Walk Away";
    b->releaseYear = 1993;
    b->genre = "Pop";
    b->length = 4.58;

    insertEnd(2, "Taylor Swift", "You Belong With Me", 2008, "Pop", 3.48, b);
    insertEnd(3, "The Cranberries", "Promises", 1999, "Rock", 4.30, b);

    songLinkedList* newHead = insertHead(4, "Maria Carey", "All I Want For Christmas Is You", 1994, "Seasonal", 3.55, b);

    insertEnd(5, "Selena Gomez, Kygo", "It Ain't Me", 2017, "Dance-pop", 3.41, newHead);

    printLinkedList(newHead);
}