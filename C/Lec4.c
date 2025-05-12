#include <stdio.h>

int main() {
    char gender;
    int age;

    printf("What is your Gender (M/F): ");
    scanf("%c", &gender);

    printf("What is your age: ");
    scanf("%d", &age);

    if (gender == 'F' || age > 12) {
        printf("You get a Free Ice Cream");
    } else {
        printf("You are not entitled to a free ice cream");
    }

}