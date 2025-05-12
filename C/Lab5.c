#include <stdio.h>

int main() {
    int sum;
    for (int i=1; i<=50; i++) {
        sum += i;
        printf("%d", sum);
    }

    int num;
    while (num<=100) {
        if (!num%2) {
            printf("%d", num);
        }
        num++;
    }

    int nonNegative;
    int enteredInt;
    do {
        nonNegative = enteredInt;
        printf("Enter a number (negative to stop): ");
        scanf("%d", &enteredInt);
    } while (enteredInt>=0);
    printf("Last non-negative number entered was: %d", nonNegative);

    for (int i; i<5; i++) {
        for (int j; j<5; j++) {
            printf("x  ");
        }
        printf("\n");
    }

    char* enteredPin;
    char* correctPin=1234;
    int tries;
    do {
        printf("Please enter your PIN: ");
        scanf("%s", &enteredPin);
        
        if (enteredPin == correctPin) {
            printf("Withdrawal successful");
            break;
        } else if (tries==2) {
            printf("Card blocked");
            break;
        } else {
            printf("Incorect PIN.");
        }
        tries++;
    } while (tries<3);
}