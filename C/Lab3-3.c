#include <stdio.h>

int main() {
    int num1, num2;

    printf("Enter the first number: ");
    scanf("%d", &num1);
   
    printf("Enter the second number: ");
    scanf("%d", &num2);

    if (num1 > num2) {
        printf("a: %d is greater than b: %d", num1, num2);
    } else {
        printf("b: %d is greater than a: %d", num2, num1);
    }
}