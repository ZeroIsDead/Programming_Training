#include <stdio.h>

int main() {
    int numTests;
    int k, n;
    int currentNum;

    scanf("%i", &numTests);
    for (int j=0; j<numTests; j++) {
        scanf("%i %i", &k, &n);

        int firstElem = 0;
        int min = 0;
        for (int i=0; i<k; i++) {
            scanf("%i", &currentNum);
            if (firstElem == 0) {
                min = currentNum;
                firstElem = 1;
                continue;
            }

            if (min > currentNum) {
                min = currentNum;
            }
        }
        if (min > n) {
            printf("%i\n", n);
        } else if (min == 0 || min == 1) {
            printf("0\n");
        } else {
            printf("%i\n", min -1);
        }
    }
}