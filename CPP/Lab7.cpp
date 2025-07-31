#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

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
    while (list) {
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

    if (list == nullptr) {
        return node;
    }

    while (list) {
        if (list->next == nullptr) {
            break;
        }

        list = list->next;
    }

    list->next = node;

    return head;
}

songLinkedList* deleteHead(songLinkedList* list) {
    if (!list) return nullptr;

    songLinkedList* next = list->next;

    list->next = nullptr;
    delete list;

    return next;
}



songLinkedList* deleteEnd(songLinkedList* list) {
    if (!list) return nullptr;

    if (!list->next) {
        delete list;
        return nullptr;
    }

    songLinkedList* current = list;
    while (current->next->next) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;

    return list;
}

songLinkedList* deleteArtist(songLinkedList* list, const string& name) {
    while (list && list->artistName == name) {
        songLinkedList* temp = list;
        list = list->next;
        delete temp;
    }

    songLinkedList* current = list;
    while (current && current->next) {
        if (current->next->artistName == name) {
            songLinkedList* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    return list;
}

songLinkedList* deleteGenre(songLinkedList* list, const string& genre) {
    while (list && list->genre == genre) {
        songLinkedList* temp = list;
        list = list->next;
        delete temp;
    }

    songLinkedList* current = list;
    while (current && current->next) {
        if (current->next->genre == genre) {
            songLinkedList* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    return list;
}

songLinkedList* deleteSongNumber(songLinkedList* list, int number) {
    while (list && list->id == number) {
        songLinkedList* temp = list;
        list = list->next;
        delete temp;
    }

    songLinkedList* current = list;
    while (current && current->next) {
        if (current->next->id == number) {
            songLinkedList* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    return list;
}

songLinkedList* sort(songLinkedList* list) {
    if (!list || !list->next) return list;

    songLinkedList* sorted = nullptr;

    while (list) {
        songLinkedList* node = list;
        list = list->next;
        node->next = nullptr;

        if (!sorted || node->id < sorted->id) {
            node->next = sorted;
            sorted = node;
        } else {
            songLinkedList* current = sorted;
            while (current->next && current->next->id < node->id) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }
    return sorted;
}



int main() {
    songLinkedList* b = new songLinkedList();

    b->id = 1;
    b->artistName = "Celine Dion";
    b->songName = "Just Walk Away";
    b->releaseYear = 1993;
    b->genre = "Pop";
    b->length = 4.58;

    b = insertEnd(2, "Taylor Swift", "You Belong With Me", 2008, "Pop", 3.48, b);
    b = insertEnd(3, "The Cranberries", "Promises", 1999, "Rock", 4.30, b);

    songLinkedList* newHead = insertHead(4, "Maria Carey", "All I Want For Christmas Is You", 1994, "Seasonal", 3.55, b);

    newHead = insertEnd(5, "Selena Gomez, Kygo", "It Ain't Me", 2017, "Dance-pop", 3.41, newHead);

    // printLinkedList(newHead);

    ifstream file("Lab7.csv");

    songLinkedList* songlist = nullptr;

    string line;
    while (getline(file, line)) {
        string row[6];
        stringstream ss(line);
        string cell;

        int i = 0;
        // Split line by comma
        while (getline(ss, cell, ',')) {
            row[i++] = (cell);
        }

        songlist = insertEnd(stoi(row[0]), row[1], row[2], stoi(row[3]), row[4], stod(row[5]), songlist);

    }

    file.close();

    printLinkedList(songlist);

    songlist = deleteHead(songlist);
    cout << "_____DELETE HEAD_____" << endl;

    printLinkedList(songlist);


    songlist = deleteEnd(songlist);
    cout << "_____DELETE END_____" << endl;
    printLinkedList(songlist);

    songlist = insertEnd(12, "The Cranberries", "Promises", 1999, "Rock", 4.30, songlist);
    songlist = insertEnd(11, "The Cranberries", "Promises", 1999, "Rock", 4.30, songlist);
    songlist = insertEnd(10, "The Cranberries", "Promises", 1999, "Rock", 4.30, songlist);
    songlist = insertEnd(9, "The Cranberries", "Promises", 1999, "Rock", 4.30, songlist);


    songlist = deleteArtist(songlist, "Selena Gomez, Kygo");
    cout << "_____DELETE Artist_____" << endl;
    printLinkedList(songlist);

    songlist = deleteSongNumber(songlist, 2);
    cout << "_____DELETE Song Number_____" << endl;
    printLinkedList(songlist);

    songlist = deleteGenre(songlist, "Pop");
    cout << "_____DELETE GENRE_____" << endl;
    printLinkedList(songlist);


    cout << "_____SORTED_____" << endl;
    printLinkedList(sort(songlist));

}