#include <stdio.h>

int main() {
    int age;

    do {
        printf("Enter your age: ");
        scanf("%d", &age);
    
        printf("Your Age: %d\n", age);
    } while (age!=0);
}