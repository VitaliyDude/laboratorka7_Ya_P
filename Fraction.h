#pragma once
#include <iostream>
#include <stdexcept>
#include <cstdlib> // Для std::abs

// Класс для работы с дробями
class Fraction {
    int numerator; // Числитель
    int denominator; // Знаменатель

public:
    
    Fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { // Конструктор с параметрами по умолчанию
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        normalize(); // Нормализация дроби
    }

    // Перегрузки


    Fraction operator +(const Fraction& other) const { // +
        int lcm_value = lcm(denominator, other.denominator); // наименьшее общее кратное знаменателей
        int n = numerator * (lcm_value / denominator) + other.numerator * (lcm_value / other.denominator); // Сумма числителей
        return Fraction(n, lcm_value);
    }

    Fraction operator -(const Fraction& other) const { // -
        int lcm_value = lcm(denominator, other.denominator); 
        int n = numerator * (lcm_value / denominator) - other.numerator * (lcm_value / other.denominator); 
        return Fraction(n, lcm_value); 
    }

    Fraction operator /(int value) const { // /
        return Fraction(numerator, denominator * value); 
    }

    bool operator <(const Fraction& other) const { // <
        return numerator * other.denominator < other.numerator * denominator; // Сравнение дробей
    }

    bool operator >(const Fraction& other) const { // >
        return numerator * other.denominator > other.numerator * denominator; // Сравнение дробей
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) { // <<
        os << fraction.numerator << "/" << fraction.denominator; 
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Fraction& f) { // >>
        char sep;
        is >> f.numerator >> sep >> f.denominator;
        if (f.denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        f.normalize();
        return is;
    }


private:
    
    void normalize() { // Нормализация дроби
        int gcd_value = gcd(numerator, denominator); // наибольший общий делитель числителя и знаменателя
        numerator /= gcd_value; // Деление числителя на наибольший общий делитель
        denominator /= gcd_value; // Деление знаменателя на наибольший общий делитель
        if (denominator < 0) { 
            numerator = -numerator; // Изменение знака числителя
            denominator = -denominator; // Изменение знака знаменателя
        }
    }

    int gcd(int a, int b) const { // Наибольший общий делитель
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return std::abs(a);
    }

    int lcm(int a, int b) const { // Наименьшее общее кратное
        return std::abs(a * b) / gcd(a, b); // НОК через НОД
    }
};