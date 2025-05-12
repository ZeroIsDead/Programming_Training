#include <stdio.h>

int main() {
    int num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;

    for (int i=0; i<10; i++) {
        sum += num[i];
    }

    printf("Sum of the array elements is: %d\n", sum);

    int length;

    printf("How many numbers you want to enter (up to 10)? ");
    scanf("%d", &length);

    int number[length];
    int product = 1;

    printf("Enter %d numbers:\n", length);
    for (int i=0; i<length; i++) {
        printf("Number %d: ", i+1);
        scanf("%d", &number[i]);
    }

    for (int i = 0; i<length; i++) {
        product *= number[i];
    }

    printf("The product of the entered numbers is: %d\n", product);

    int array[4][4] = {
        {1  , 2   , 3   ,    4},
        {5  , 6   , 7   ,    8},
        {9  , 10 , 11 , 12},
        {13, 14 , 15,  16}
    };
    sum = 0;

    for (int i=0; i<4; i++) {
        sum += array[i][i];
    }

    printf("Sum of the diagonal elements is: %d\n", sum);


}