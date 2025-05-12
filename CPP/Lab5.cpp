#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void swap(int*& value1, int*& value2) {
    int* temp = value2;
    value2 = value1;
    value1 = temp;

    cout << "After swapping in swap function : " << endl;
    cout << "Value of value1 = " << *value1 << endl;
    cout << "Value of value2 = " << *value2 << endl;
}

void convert(double* val) {
    *val = *val * 2.54;
}

double getLength() {
    double length;

    cout << "Enter Length of Rectangle: ";
    cin >> length;

    return length;
}

double getWidth() {
    double width;

    cout << "Enter Width of Rectangle: ";
    cin >> width;

    return width;
}

double getArea(double length, double width) {
    return length * width;
}

void displayData(double& length, double& width, double& area) {
    cout << "Rect Length = " << length << "; Rect Width = " << width << "; Rect Area = " << area << endl;
}

double calcAverage(int* arr, int size) {
    int sum = 0;
    for (int i=0; i<size; i++) {
        sum += arr[i];
    }

    return sum / size;
}

int findLowest(int* arr, int size) {
    int low = arr[0];
    for (int i =0; i<size; i++) {
        if (low > arr[i]) {
            low = arr[i];
        }
    }

    return low;
}

void displayResult(string* correct, string* answer, int size) {
    int marks = 0;

    for (int i =0; i<size; i++) {
        if (correct[i] == answer[i]) {
            marks++;
        }
    }

    if (marks >= 15) {
        cout << "Student Passed!" << endl;
    } else {
        cout << "Student Failed!" << endl;
    }
}


int main() {
    string word = "abc";
    int integer = 1;
    float real = 10.4f;
    long long biginteger = 98989898911;

    cout << "Value of character = " << word << ", Address of character = " << &word << endl; 
    cout << "Value of integer = " << integer << ", Address of character = " << &integer << endl;
    cout << "Value of real = " << real << ", Address of character = " << &real << endl;
    cout << "Value of biginteger = " << biginteger << ", Address of character = " << &biginteger << endl;


    int num = 10;
    int* ptr;

    ptr = &num;

    cout << "Address of num = " << &num << endl;
    cout << "Value of num = " << num << endl << endl;

    cout << "Address of ptr = " << &ptr << endl;
    cout << "Value of ptr = " << ptr << endl;
    cout << "Value pointed by ptr = " << *ptr << endl;

    int num1, num2, sum;
    int* ptr1,* ptr2;

    cout << "Enter any two numbers : ";
    cin >> num1 >> num2;

    ptr1 = &num1;
    ptr2 = &num2;

    cout << "Address of num1 = " << &num1 << "; Value of num1 = " << num1 << endl;
    cout << "Address of num2 = " << &num2 << "; Value of num2 = " << num2 << endl;

    cout << "Address of ptr1 = " << &ptr1 << "; Value of ptr1 = " << *ptr1 << endl;
    cout << "Address of ptr2 = " << &ptr2 << "; Value of ptr2 = " << *ptr2 << endl;

    cout << "Sum = " << num1 + num2 << endl;

    cout << "Before swapping in main function : " << endl;
    cout << "Value of num1 = " << *ptr1 << endl;
    cout << "Value of num2 = " << *ptr2 << endl;

    swap(ptr1, ptr2);

    cout << "After swapping in main function : " << endl;
    cout << "Value of num1 = " << *ptr1 << endl;
    cout << "Value of num2 = " << *ptr2 << endl;
    

    int arraySize;

    cout << "Enter the size of array: ";
    cin >> arraySize;

    int* array = new int[arraySize];

    for (int i =0; i<arraySize; i++) {
        cin >> array[i];
    }

    cout << "The array elements = ";

    for (int i =0; i<arraySize; i++) {
        cout << array[i] << " , ";
    }

    cout << endl;


    double measurement;

    cout << "Enter a length in inches, and I will convert" << endl;
    cout << "it to centimeters: ";
    cin >> measurement;
    convert(&measurement);
    cout << fixed << setprecision(4);
    cout << "Value in centimeters: " << measurement << endl;

    double length = getLength();
    double width = getWidth();
    double area = getArea(length, width);
    displayData(length, width, area);

    int arrSize;
    cout << "Enter number of subjects: ";
    cin >> arrSize;

    int* arr = new int[arrSize];

    for (int i=0; i<arrSize; i++) {
        while (true) {
            cin >> arr[i];
            if (arr[i] >= 0) {
                break;
            }
        }
        
    }

    double avg = calcAverage(arr, arrSize);
    double low = findLowest(arr, arrSize);

    cout << "Average = " << avg << " Lowest = " << low << endl;

    string* ans = new string[20]{"B", "D", "A", "A", "C", "A", "B", "A", "C", "D", "B", "C", "D", "A", "D", "C", "C", "B", "D", "A"};

    string* stuAns = new string[20];

    cout << "Answer the Following Questions with A,B,C,D: " << endl;

    for (int i =0; i<20; i++) {
        while (true) {
            cin >> stuAns[i];
            if (stuAns[i] == "A") {
                break;
            }
            if (stuAns[i] == "B") {
                break;
            }
            if (stuAns[i] == "C") {
                break;
            }
            if (stuAns[i] == "D") {
                break;
            }
        }
    }

    displayResult(ans, stuAns, 20);

    delete ptr1, ptr2;
    delete[] ans, stuAns, arr, array;

    return 0;
}