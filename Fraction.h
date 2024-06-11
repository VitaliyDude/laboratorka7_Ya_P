#pragma once
#include <iostream>
#include <stdexcept>
#include <cstdlib> // ��� std::abs

// ����� ��� ������ � �������
class Fraction {
    int numerator; // ���������
    int denominator; // �����������

public:
    
    Fraction(int n = 0, int d = 1) : numerator(n), denominator(d) { // ����������� � ����������� �� ���������
        if (denominator == 0) {
            throw std::invalid_argument("����������� �� ����� ���� ����� ����");
        }
        normalize(); // ������������ �����
    }

    // ����������


    Fraction operator +(const Fraction& other) const { // +
        int lcm_value = lcm(denominator, other.denominator); // ���������� ����� ������� ������������
        int n = numerator * (lcm_value / denominator) + other.numerator * (lcm_value / other.denominator); // ����� ����������
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
        return numerator * other.denominator < other.numerator * denominator; // ��������� ������
    }

    bool operator >(const Fraction& other) const { // >
        return numerator * other.denominator > other.numerator * denominator; // ��������� ������
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) { // <<
        os << fraction.numerator << "/" << fraction.denominator; 
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Fraction& f) { // >>
        char sep;
        is >> f.numerator >> sep >> f.denominator;
        if (f.denominator == 0) {
            throw std::invalid_argument("����������� �� ����� ���� ����� ����");
        }
        f.normalize();
        return is;
    }


private:
    
    void normalize() { // ������������ �����
        int gcd_value = gcd(numerator, denominator); // ���������� ����� �������� ��������� � �����������
        numerator /= gcd_value; // ������� ��������� �� ���������� ����� ��������
        denominator /= gcd_value; // ������� ����������� �� ���������� ����� ��������
        if (denominator < 0) { 
            numerator = -numerator; // ��������� ����� ���������
            denominator = -denominator; // ��������� ����� �����������
        }
    }

    int gcd(int a, int b) const { // ���������� ����� ��������
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return std::abs(a);
    }

    int lcm(int a, int b) const { // ���������� ����� �������
        return std::abs(a * b) / gcd(a, b); // ��� ����� ���
    }
};