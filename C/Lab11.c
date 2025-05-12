#include <stdio.h>

int main() {
    int m = 10;
    int n, o;
    int* z = &m;

    printf("Pointer : Show the basic declaration of pointer :\n--------------------------------------------------------------------");
    printf("Here is m=10, n and o are two integer variable and *z is an integer\n\nz stores the address of m = %p\n\n *z stores the value of m = %d\n\n", z, *z);
    printf("&m is the address of m = %p\n\n &n stores the address of n = %p\n\n &o stores the address of o = %p\n\n &z stores the address of z = %p\n\n\n", &m, &n, &o, &z);


    m = 29;
    int* ab = &m;

    printf("Pointer : How to handle the pointers in the program :\n-----------------------------------------------------------------------------\n");
    printf("Here in the delcaration of ab = int pointer, int m = 29, address of m : %p\nValue of m : %d\n", &m, m);
    printf("Now ab is assigned with the address of m\nAddress of pointer ab: %p\nContent of pointer ab : %d\n\n", ab, *ab);
    printf("The value of m assigned to 34 now.\nAddress of pointer ab : %p\nContent of pointer ab : %d\n\n", ab, *ab);
    printf("The pointer variable ab is assigned the value 7 now.\nAddress of m : %p\nValue of m : %d\n\n", ab, m);

    int num1, num2;
    int* pt1 = &num1;
    int* pt2 = &num2;

    printf("Pointer : Add two numbers :\n------------------------------------------------\nInput the first number : ");
    scanf("%d", pt1);
    printf("Input the second number: ");
    scanf("%d", pt2);

    printf("The sum of the entered numbers is : %d", *pt1+*pt2);

}