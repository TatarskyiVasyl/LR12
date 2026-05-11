#include <iostream>
#include <cmath>

int calculateFactorial(int number) {
    if (number <= 1)
        return 1;
    return number * calculateFactorial(number - 1);
}

bool isPrime(int value) {
    if (value < 2) return false;
    for (int divisor = 2; divisor <= sqrt(value); divisor++) {
        if (value % divisor == 0)
            return false;
    }
    return true;
}

struct Point {
    double x;
    double y;
};

double calculateDistance(Point pointA, Point pointB) {
    double deltaX = pointA.x - pointB.x;
    double deltaY = pointA.y - pointB.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

int main() {
    int number = 5;
    int result = calculateFactorial(number);
    std::cout << "Factorial: " << result << std::endl;

    int value = 17;
    bool primeCheck = isPrime(value);
    std::cout << "Is prime: " << primeCheck << std::endl;

    Point pointA = {3.0, 4.0};
    Point pointB = {0.0, 0.0};
    double distance = calculateDistance(pointA, pointB);
    std::cout << "Distance: " << distance << std::endl;

    return 0;
}
