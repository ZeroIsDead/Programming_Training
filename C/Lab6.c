#include <stdio.h>

void printS() {
    printf("I love C Programming so freaking much yayy!\n");
}

void intParity(int num) {
    if (num % 2) {
        printf("%d is odd\n", num);
    } else {
        printf("%d is even\n", num);
    }
}

int askForInt() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    return num;
}

int sum(int num1, int num2) {
    return num1 + num2;
}

float trianglePerimeter(float side1, float side2, float side3) {
    return side1 + side2 + side3;
}

int login(int userID, int password, int correctID, int correctPassword) {
    return (userID == correctID && password == correctPassword);
}

int main() {
    printS();

    intParity(5);

    printf("You entered: %d\n", askForInt());

    printf("The sum is: %d\n", sum(3, 4));

    printf("The perimeter is: %.2f\n", trianglePerimeter(3.5, 4.2, 5.1));

    // Pre-defined ID and password for each roles 
    int correctAdminID = 1, correctAdminPassword = 1111;
    int correctDoctorID = 2, correctDoctorPassword = 2222;
    int correctNurseID = 3, correctNursePassword = 3333;
    int correctPatientID = 4, correctPatientPassword = 4444;

    // Input credentials for the user trying to log in
    int userID, userPassword;

    // Admin login
    printf("Admin, enter your ID: ");
    scanf("%d", &userID);
    printf("Admin, enter your password: ");
    scanf("%d", &userPassword);
    if (login(userID, userPassword, correctAdminID, correctAdminPassword)) {
        printf("Admin login successful.\n");
    } else {
        printf("Admin login failed.\n");
    }

    // Doctor login
    printf("Doctor, enter your ID: ");
    scanf("%d", &userID);
    printf("Doctor, enter your password: ");
    scanf("%d", &userPassword);
    if (login(userID, userPassword, correctDoctorID, correctDoctorPassword)) {
        printf("Doctor login successful.\n");
    } else {
        printf("Doctor login failed.\n");
    }

    // Nurse login
    printf("Nurse, enter your ID: ");
    scanf("%d", &userID);
    printf("Nurse, enter your password: ");
    scanf("%d", &userPassword);
    if (login(userID, userPassword, correctNurseID, correctNursePassword)) {
        printf("Nurse login successful.\n");
    } else {
        printf("Nurse login failed.\n");
    }

    // Patient login
    printf("Admin, enter your ID: ");
    scanf("%d", &userID);
    printf("Admin, enter your password: ");
    scanf("%d", &userPassword);
    if (login(userID, userPassword, correctPatientID, correctPatientPassword)) {
        printf("Patient login successful.\n");
    } else {
        printf("Patient login failed.\n");
    }
}

