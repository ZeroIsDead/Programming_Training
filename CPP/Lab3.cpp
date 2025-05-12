#include <iostream>
#include <chrono>

using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double ChangeQuizScoreToPercentage(int score) {
    return score * 0.2;
}

double ChangeMidTermScoreToPercentage(int score) {
    return score * 0.5;
}

double ChangeFinalScoreToPercentage(int score) {
    return score * 0.3;
}

string Check_Grade(double avg) {
    if (avg >= 90) {return "A";}
    else if (avg >= 70) {return "B";}
    else if (avg >= 50) {return "C";}
    else {return "F";}
}

int main() {
    int* arr = new int[10];

    int buffer = 0;
    bool skip;

    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    chrono::nanoseconds duration;

    for (int i=0; i<10; i++) {
        while (true) {
            skip = true;
            cout << "Enter value " << i+1 << ": ";
            cin >> buffer;

            start = chrono::high_resolution_clock::now();
    
            for (int j=0; j<i; j++) {
                if (buffer == arr[j]) {
                    skip = false;
                    break;
                }
            }

            end = chrono::high_resolution_clock::now();

            duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

            cout << "Time taken: " << duration.count() << " ns" << endl;

            start = chrono::high_resolution_clock::now();

            int left = 0, right = i;

            while (left<=right) {
                int middle = left + (right - left) / 2;


                if (arr[middle] == buffer) {
                    skip = false;
                    break;
                }

                if (arr[middle] < buffer) {
                    left = middle + 1;
                }

                if (arr[middle] > buffer) {
                    right = middle - 1;
                }
            }

            end = chrono::high_resolution_clock::now();

            duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

            cout << "Time taken: " << duration.count() << " ns" << endl;

            if (skip) {
                arr[i] = buffer;
                break;
            }
        }
    }

    for (int i=0; i<10; i++) {
        cout << arr[i] << ",";
    }
    cout << endl;

    int billy[] = {4,2,1,3,5};

    start = chrono::high_resolution_clock::now();

    insertionSort(billy, 5);

    for (int i=0; i<5; i++) {
        cout << billy[i] << ", ";
    }
    cout << endl;

    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "Time taken: " << duration.count() << " ns" << endl;

    start = chrono::high_resolution_clock::now();

    bubbleSort(billy, 5);

    for (int i=0; i<5; i++) {
        cout << billy[i] << ", ";
    }
    cout << endl;

    end = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "Time taken: " << duration.count() << " ns" << endl;

    string** studentRecords = new string*[5];

    for (int i=0; i<5; i++) {
        studentRecords[i] = new string[7];

        cout << "Enter Name: ";
        cin >> studentRecords[i][0];

        cout << "Enter Student TP: ";
        cin >> studentRecords[i][1];

        cout << "Enter 3 Scores (Quiz, Mid Term, Final Exam): ";
        cin >> studentRecords[i][2] >> studentRecords[i][3] >> studentRecords[i][4];

        double avg = (ChangeQuizScoreToPercentage(stoi(studentRecords[i][2]))
        + ChangeMidTermScoreToPercentage(stoi(studentRecords[i][3])) 
        + ChangeFinalScoreToPercentage(stoi(studentRecords[i][4]))) / 3;

        studentRecords[i][5] = to_string(avg);

        studentRecords[i][6] = Check_Grade(avg);
    }

    cout << "Student Name\tStudent TP\tQuiz (20)\tMid Term (50)\tFinal Exam (30)\tTotal Score(100)\tGrade" << endl;
    for (int i=0; i<5; i++) {
        for (int j=0; j<7; j++) {
            cout << studentRecords[i][j] << "\t";
        }
        cout << endl;
    }


    int n;

    cout << "Enter how many random numbers you want to do an analysis? ";
    cin >> n;

    int* sample = new int[n];
    int length = 10;
    
    for (int i =0; i<n; i++) {
        srand(time(0)); 

        sample[i] = rand() % 50 + 1;

        cout << sample[i] << "\t";

        if (i+1 % length == 0) {
            cout << endl;
        }
    }

    bubbleSort(sample, n);

    cout << "The analysis star design as below:\n-----------------------------------------------------------------------\n1 - 10 |";

    bool catA = false, catB = false, catC = false, catD = false, catE = false;
    for (int i=0; i<n; i++) {
        cout << "\t" << "*";
        if (11 <= sample[i] && !catB) {
            catB = true;
            cout << endl << "11 - 20 |";
        }
        if (21 <= sample[i] && !catC) {
            catC = true;
            cout << endl << "21 - 30 |";
        }
        if (31 <= sample[i] && !catD) {
            catD = true;
            cout << endl << "31 - 40 |";
        }
        if (41 <= sample[i] && !catE) {
            catE = true;
            cout << endl << "41 - 50 |";
        }
    }

    cout << endl << "To verify the graph is correct: (display numbers of 41 - 50)" << endl << "------------------------------------------------------------------------";

    for (int i =0; i<n; i++) {
        if (sample[i] < 41) {
            continue;
        }

        cout << sample[i] << "\t";

        if (i+1 % length == 0) {
            cout << endl;
        }
    }




}





