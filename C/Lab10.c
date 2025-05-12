#include <stdio.h>

struct Book {
    char title[100];
    char author[50];
    float price;
};

struct Rectangle {
    float length;
    float width;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    char name[50];
    int employeeID;
    float salary;
};

int main() {
    struct Book book;

    printf("Enter book title: ");
    scanf("%s", book.title);

    printf("Enter author's name: ");
    scanf("%s", book.author);

    printf("Enter price: ");
    scanf("%f", &book.price);

    printf("Book Details:");
    printf("Title: %s\nAuthor: %s\nPrice %f", book.title, book.author, book.price);

    printf("\n\n");
    
    struct Rectangle rect;

    printf("Enter length of rectangle: ");
    scanf("%f", &rect.length);

    printf("Enter width of rectangle: ");
    scanf("%f", &rect.width);

    printf("Area: %f\nPerimeter: %f", rect.length*rect.width, 2*(rect.length+rect.width));

    printf("\n\n");

    struct Date date;

    printf("Enter day: ");
    scanf("%d", &date.day);

    printf("Enter motnh: ");
    scanf("%d", &date.month);

    printf("Enter year: ");
    scanf("%d", &date.year);

    printf("%02d/%02d/%04d", date.day, date.month, date.year);

    printf("\n\n");

    struct Employee emp;

    printf("Enter employee name: ");
    scanf("%s", emp.name);

    printf("Enter employee ID: ");
    scanf("%d", &emp.employeeID);

    printf("Enter salary: ");
    scanf("%f", &emp.salary);

    printf("Employee Details:\nName: %s\nEmployee ID: %d\nSalary: %f",emp.name, emp.employeeID, emp.salary);
}