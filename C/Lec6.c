#include <stdio.h>

void print(int total) {
    printf("The sum are: %d\n", total);
}

int getValues() {
    int num1, num2, total;
    printf("Enter first number: ");
    scanf("%d", &num1);
    
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    total = num1 + num2;
    return total;
}

void calcValues() {
    int num1, num2, total;
    printf("Enter first number: ");
    scanf("%d", &num1);
    
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    total = num1 + num2;
    printf("The sum of the two numbers is: %d\n", total);
}

int main() {
    int num1, num2, total;
    printf("Enter first number: ");
    scanf("%d", &num1);
    
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    total = num1 + num2;
    
    print(total);

    int result = getValues();
    printf("The sum of the two numbers is: %d\n", result);
    
    calcValues();
}

