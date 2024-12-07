#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

class Fraction {
    int num;
    int den;
    static int instanceCount;
public:
    Fraction(int num = 0, int den = 1): num(num), den(den) {
        reduce();
        ++instanceCount;
    }

    // Перегрузка операторов
    Fraction operator+(const Fraction& other) const {
        int newNum = num * other.den + other.num * den;
        int newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator-(const Fraction& other) const {
        int newNum = num * other.den - other.num * den;
        int newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator*(const Fraction& other) const {
        int newNum = num * other.num;
        int newDen = den * other.den;
        return Fraction(newNum, newDen);
    }

    Fraction operator/(const Fraction& other) const {
        int newNum = num * other.den;
        int newDen = den * other.num;
        return Fraction(newNum, newDen);
    }

    // Метод для сокращения дроби
    void reduce() {
        int gcdValue = gcd(num, den);
        num /= gcdValue;
        den /= gcdValue;
    }

    // Статические методы
    static int gcd(int n, int m) {
        while (m != 0) {
            int temp = m;
            m = n % m;
            n = temp;
        }
        return n;
    }

    static void printAsFraction(double decimal_fraction) {
        int precision = 1000000; // Точность до 6 знаков после запятой
        int num = static_cast<int>(decimal_fraction * precision);
        int den = precision;
        int gcdValue = gcd(num, den);
        num /= gcdValue;
        den /= gcdValue;
        std::cout << num << "/" << den << std::endl;
    }

    static void printAsFraction(char* decimal_fraction) {
        double value = std::atof(decimal_fraction);
        printAsFraction(value);
    }

    // Статический член для подсчета экземпляров
    static int getInstanceCount() { return instanceCount; }

    // Метод для вывода дроби
    void print() const { std::cout << num << "/" << den << std::endl; }
};

// Инициализация статического члена
int Fraction::instanceCount = 0;

int main() {
    Fraction f1(1, 4);
    Fraction f2(1, 2);

    Fraction f3 = f1 + f2;
    Fraction f4 = f1 - f2;
    Fraction f5 = f1 * f2;
    Fraction f6 = f1 / f2;

    std::cout << "f1: ";
    f1.print();
    std::cout << "f2: ";
    f2.print();
    std::cout << "f1 + f2: ";
    f3.print();
    std::cout << "f1 - f2: ";
    f4.print();
    std::cout << "f1 * f2: ";
    f5.print();
    std::cout << "f1 / f2: ";
    f6.print();

    std::cout << "0.43 as fraction: ";
    Fraction::printAsFraction(0.43);

    char decimal_fraction[] = "0.25";
    std::cout << "0.25 as fraction: ";
    Fraction::printAsFraction(decimal_fraction);

    std::cout << "Total instances: " << Fraction::getInstanceCount() << std::endl;

    return 0;
}