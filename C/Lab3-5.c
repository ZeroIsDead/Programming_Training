#include <stdio.h>

int main() {
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    if (number % 5 == 0) {
        printf("Divisible by 5");
    } else {
        printf("Not divisible by 5");
    }
}