#include <stdio.h>

int main() {
    int num[5];
    printf("Enter 5 integers:\n");

    for (int i=0; i<5; i++) {
        scanf("%d", &num[i]);
    }

    printf("Displaying Integers:\n");
    
    for (int i=0; i<5; i++) {
        printf("%d\n", num[i]);
    }

    int numArray[3][4] = {{3, 7, 5, 11}, {4,9,5,7}, {2, 3, 7, 8}};

    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
            printf("%d ", numArray[i][j]);
        }
        printf("\n");
    }


}