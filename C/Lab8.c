#include <stdio.h>

int main() {
    char input[256];

    printf("String: ");
    fgets(input, 256, stdin);

    int count = 0;
    for (int i=0; input[i] != '\n'; i++) {
        count++;
    }

    printf("Length of the string is: %d\n", count);


    char input1[256];
    char output[256];


    printf("Normal string is: ");
    fgets(input1, 256, stdin);

    count = 0;
    for (int i=0; input1[i] != '\n'; i++) {
        count++;
    }

    for (int i=0; input1[i] != '\n'; i++) {
        output[i] = input1[count-i-1];
    }

    printf("Reversed string is: %s\n", output);

    char input2[256];
    char output1[256];

    printf("Normal string is: ");
    fgets(input2, 256, stdin);

    count = 0;
    for (int i=0; input2[i] != '\n'; i++) {
        output1[i] = input2[i];
        count++;
    }
    output1[count] = '\0';

    printf("Copied string is: %s\n", output1);

    char input3[256];
    char input4[256];
    char output3[256];

    printf("First Name: ");
    fgets(input3, 256, stdin);

    printf("Last Name: ");
    fgets(input4, 256, stdin);

    int firstStringLen = 0;
    for (int i=0; input3[i] != '\n'; i++) {
        output3[i] = input3[i];
        firstStringLen++;
    }

    output3[firstStringLen] = ' ';
    firstStringLen++;

    int secondStringLen = 0;
    for (int i=0; input4[i] != '\n'; i++) {
        output3[i+firstStringLen] = input4[i];
        secondStringLen++;
    }

    output3[firstStringLen+secondStringLen] = '\0';

    printf("Concatenated string is: %s", output3);
}