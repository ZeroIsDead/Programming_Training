#include <stdio.h>

int main() {
    int num1,num2,num3;

    printf("Enter the first number: ");
    scanf("%d", &num1);
   
    printf("Enter the second number: ");
    scanf("%d", &num2);

    printf("Enter the third number: ");
    scanf("%d", &num3);

    if (num1 >= num2 && num1 >= num3) {
        printf("First number is largest: %d", num1);
    } else if (num2 >= num3 && num2 >= num1) {
        printf("Second number is largest : %d", num2);
    } else {
        printf("Third number is largest: %d", num3);
    }
}