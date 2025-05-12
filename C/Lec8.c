#include <stdio.h>

int main() {
    char string[225];
    
    printf("Accept a string from keyboard:\n--------------------------------\nInput the string : ");
    fgets(string, sizeof(string), stdin);
    
    printf("The string you entered is : ");
    puts(string);

    printf("Find the length of a string :\n--------------------------------\nInput the string : ");
    fgets(string, sizeof(string), stdin);

    int length = 0;

    while (string[length] != '\0') {
        length++;
    }
    printf("Length of the string is : %d\n\n", length-1);


    printf("Seperate the individual characters from a string :\n--------------------------------\nInput the string : ");
    fgets(string, sizeof(string), stdin);

    printf("The characters of the stirng are :\n");
    for (int i=0; string[i]!='\0'; i++) {
        printf("%c ", string[i]);
    }



}