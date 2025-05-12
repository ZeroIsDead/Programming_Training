#include <iostream>
#include <string>

using namespace std;

int main() {
    int feet, inches;

    cin >> feet >> inches;

    cout << (feet * 12 + inches) * 2.54 << endl;

    int x = 1;
    int y = 1;

    if (y > 0) {
        x = 1;
    }

    double score = 10;

    if (80 < score < 90) {
        score += 5;
    }

    cout << (x % 2 == 1) && x > 0;

    cout << (x > 0) && (y > 0);

    int ticket = 0;

    int speed = 0;

    if (speed > 55) {
        ticket = 1;
    }

    return 0;
}