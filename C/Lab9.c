#include <stdio.h>

int sum(int num1, int num2) {
    return num1 + num2;
}

int main() {
    int num;
    
    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num > 0) {
        printf("The number is positive.\n");
    } else if (num < 0) {
        printf("The number is negative.\n");
    } else {
        printf("The number is zero.\n");
    }

    for (int i=1; i<=10; i++) {
        printf("%d\n", i*2);
    }


    int num2, num3;
    printf("Emter two integers: ");
    scanf("%d %d", &num2, &num3);
    printf("Sum: %d\n", sum(num2, num3));

    int numArr[5];
    printf("Enter 5 integers: ");
    scanf("%d %d %d %d %d", &numArr[0], &numArr[1], &numArr[2], &numArr[3], &numArr[4]);

    int max = 0;
    for (int i=0; i<5; i++) {
        if (max < numArr[i]) {
            max = numArr[i];
        }
    }

    printf("Largest number: %d\n", max);

    int matrix[2][2], matrix2[2][2];

    printf("Enter elements for matrix A\n");

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Enter elements for matrix B\n");

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }    

    printf("Resultant matrix\n");
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            printf("%d ", sum(matrix[i][j], matrix2[i][j]));
        }
        printf("\n");
    }



}