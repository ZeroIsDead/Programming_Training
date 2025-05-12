#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Function to validate and convert HH:MM:SS to seconds
int elapsedTimeInSeconds(string timeStr) {
    int h, m, s;
    char sep1, sep2;
    stringstream ss(timeStr);
    ss >> h >> sep1 >> m >> sep2 >> s;

    if (sep1 != ':' || sep2 != ':' || h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
        cout << "Invalid time format!" << endl;
        return -1;
    }
    return h * 3600 + m * 60 + s;
}

// Convert full month name to lowercase
string ConvertLetterString(string month) {
    for (char& c : month)
        c = tolower(c);
    return month;
}

// Return number of days in the month (assuming non-leap year)
int FindDaysInMonth(string month) {
    month = ConvertLetterString(month);
    if (month == "january" || month == "march" || month == "may" || month == "july" || month == "august" || month == "october" || month == "december")
        return 31;
    else if (month == "april" || month == "june" || month == "september" || month == "november")
        return 30;
    else if (month == "february")
        return 28;
    else
        return 0;
}

// Take weather data and count hot, rainy, and cloudy days
void weatherReport(int days, int &hot, int &rainy, int &cloudy) {
    hot = rainy = cloudy = 0;
    char input;

    for (int i = 1; i <= days; ++i) {
        do {
            cout << "Day " << i << " : Enter 'H' for Hot, 'R' for Rainy, 'C' for Cloudy, ('E' to end): ";
            cin >> input;
            input = toupper(input);
        } while (input != 'H' && input != 'R' && input != 'C' && input != 'E');

        if (input == 'H') hot++;
        else if (input == 'R') rainy++;
        else if (input == 'C') cloudy++;
        else if (input == 'E') break;
    }
}

// Display report as a simple bar graph
void displayReport(int hot, int rainy, int cloudy) {
    cout << "\nWeather Report Summary\n";
    cout << "----------------------\n";
    cout << "Hot Days    : " << string(hot, '*') << " (" << hot << ")\n";
    cout << "Rainy Days  : " << string(rainy, '*') << " (" << rainy << ")\n";
    cout << "Cloudy Days : " << string(cloudy, '*') << " (" << cloudy << ")\n";
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int yearInputValidation(int year) {
    while (year < 1) {
        cout << "Invalid Year. Enter Again: ";
        cin >> year;
    }
    return year;
}

int monthInputValidation(int month, int year) {
    while (month < 1 || month > 12) {
        cout << "Invalid month. Enter again: ";
        cin >> month;
    }
    return month;
}

int findDaysInMonth(int month, int year) {
    int days;
    switch (month) {
        case 1: cout << "January"; days = 31; break;
        case 2: cout << "February"; days = isLeapYear(year) ? 29 : 28; break;
        case 3: cout << "March"; days = 31; break;
        case 4: cout << "April"; days = 30; break;
        case 5: cout << "May"; days = 31; break;
        case 6: cout << "June"; days = 30; break;
        case 7: cout << "July"; days = 31; break;
        case 8: cout << "August"; days = 31; break;
        case 9: cout << "September"; days = 30; break;
        case 10: cout << "October"; days = 31; break;
        case 11: cout << "November"; days = 30; break;
        case 12: cout << "December"; days = 31; break;
    }

    return days;
}


string reverseString(string text) {
    string reversed = "";
    for (int i = text.length() - 1; i >= 0; i--) {
        reversed += text[i];
    }
    return reversed;
}

bool compareString(string text1, string text2) {
    return text1 == text2;
}

void reverseDisplayNumber(int start, int end) {
    if (!start >= end) return;
    cout << end << " + ";
    reverseDisplayNumber(start, end-1);
}

int reverseDisplayNumberAndSum(int start, int end) {
    if (!start >= end) return 0;
    return end + reverseDisplayNumberAndSum(start, end-1);
}

class BankAccount {
    public:
        double balance = 0;
        double interest_rate = 0;

    public:
        void set(int dollars, int cents) {
            balance = dollars + (cents / 100.0);
        }

        void update() {
            double interest = balance * interest_rate / 100.0;
        }

        double get_balance;
};

void add1() {
    cout << 1 + 1 << endl;
}

int add2(int a, int b) {
    return a + b;
}

void add3(int a, int b) {
    cout << a + b << endl;
}

int add4() {
    return 1 + 1;
} 

int dayNumber(int day, int month, int year)
{
 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 +
             year/400 + t[month-1] + day) % 7;
}
 
string getMonthName(int monthNumber)
{
    string months[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };
 
    return (months[monthNumber]);
}

void displayCalendar(int month, int year, int days) {
    printf ("         Calendar - %d\n\n", year);
 
    int current = dayNumber (1, 1, year);
 
    int i = month-1;

    // Print the current month name
    printf("\n  ------------%s-------------\n",
            getMonthName(i).c_str());

    // Print the columns
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print appropriate spaces
    int k;
    for (k = 0; k < current; k++)
        printf("     ");

    for (int j = 1; j <= days; j++)
    {
        printf("%5d", j);

        if (++k > 6)
        {
            k = 0;
            printf("\n");
        }
    }

    if (k)
        printf("\n");

    current = k;

    return;
}

int main() {
    add1();
    cout << add2(1, 1) << endl;
    add3(1, 1);
    cout << add4() << endl; 

    int startvalue, endvalue;
    cout << "Enter a start value: ";
    cin >> startvalue;
    cout << "Enter a end value: ";
    cin >> endvalue;
    cout << endl;
    reverseDisplayNumber(startvalue, endvalue);
    cout << "= " << reverseDisplayNumberAndSum(startvalue, endvalue) << endl;
    
    string text;
    cout << "Enter a string: ";
    cin >> text;

    string reversedText = reverseString(text);
    cout << "Reverse entered String: " << reversedText << endl;

    if (compareString(text, reversedText)) {
        cout << "The entered string is a palindrome!" << endl;
    } else {
        cout << "The entered string is NOT a palindrome!" << endl;
    }
    
    int year, month, days;

    cout << "Enter calendar's year: ";
    cin >> year;
    year = yearInputValidation(year);

    cout << "Enter calendar's month: ";
    cin >> month;
    month = monthInputValidation(month, year);

    days = findDaysInMonth(month, year);

    displayCalendar(month, year, days);
    
    string timeStr;
    cout << "Please enter your elapsed time (in HH:MM:SS format) = ";
    cin >> timeStr;
    int seconds = elapsedTimeInSeconds(timeStr);
    if (seconds == -1) return 1;
    cout << "Elapsed time in seconds = " << seconds << " seconds\n\n";

    string monthString;
    cout << "Enter your Month (e.g. August): ";
    cin >> monthString; 

    days = FindDaysInMonth(monthString);
    if (days == 0) {
        cout << "Invalid month entered!" << endl;
        return 1;
    }

    int hot, rainy, cloudy;
    weatherReport(days, hot, rainy, cloudy);
    displayReport(hot, rainy, cloudy);

    return 0;

}