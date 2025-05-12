#include <stdio.h>

int main() {
    int num = 5;
    int* pt = &num;

    printf("The value of num is: %d\n", *pt);

    printf("Before Increment: %d\n", num);
    printf("After Increment: %d\n", ++*pt);

    int num1, num2;
    int* pt1 = &num1;
    int* pt2 = &num2;

    printf("Enter first number: ");
    scanf("%d", pt1);

    printf("Enter second number: ");
    scanf("%d", pt2);



    if (*pt1 > *pt2) {
        printf("The maximum number is: %d", *pt1);
    } else {
        printf("The maximum number is: %d", *pt2);
    }
}