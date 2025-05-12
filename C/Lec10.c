#include <stdio.h>
#include <string.h>

struct Car {
    char make[50];
    char model[50];
    int year;
};

void drive(struct Car car) {
    printf("Driving the %s %s\n", car.make, car.model);
}

void stop(struct Car car) {
    printf("Stopping the %s %s\n", car.make, car.model);
}

void reverse(struct Car car) {
    printf("Reversing the %s %s\n", car.make, car.model);
}

int main() {
    struct Car myCar;

    strcpy(myCar.make, "Toyota");
    strcpy(myCar.model, "Camry");
    myCar.year = 2022;

    printf("Car details: %s %s %d\n", myCar.make, myCar.model, myCar.year);

    struct Car fatherCar, motherCar;

    strcpy(fatherCar.make, "Perodua");
    strcpy(fatherCar.model, "Alive");
    fatherCar.year = 2022;

    strcpy(motherCar.make, "Honda");
    strcpy(motherCar.model, "Jazz");
    motherCar.year = 2018;

    printf("Car details: %s %s %d\n", fatherCar.make, fatherCar.model, fatherCar.year);
    printf("Car details: %s %s %d\n", motherCar.make, motherCar.model, motherCar.year);
}
