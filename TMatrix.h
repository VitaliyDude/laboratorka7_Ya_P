#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <algorithm>

template<typename T>
class TMatrix {
private:
    std::vector<std::vector<T>> matrix; // ������ ����� ������� �������
    size_t rows, cols; // ������ �������

public:
    TMatrix() : rows(0), cols(0) {} // ����������� �� ���������
    TMatrix(size_t r, size_t c) : rows(r), cols(c), matrix(r, std::vector<T>(c)) {} // ����������� � �����������

   
    T& operator()(size_t r, size_t c) {  // �������� ������� ��� ����������� ��������
        if (r >= rows || c >= cols) {
            throw std::out_of_range("�������� ������");
        }
        return matrix[r][c];
    }

    // ����������
    
    const T& operator()(size_t r, size_t c) const { // �������� ��� ������ ��������
        if (r >= rows || c >= cols) {
            throw std::out_of_range("�������� ������");
        }
        return matrix[r][c];
    }

    friend std::ostream& operator<<(std::ostream& os, const TMatrix& m) { // �������� ������ ��� ������ TMatrix
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j) {
                os << m(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }

    const std::vector<T>& operator[](size_t r) const { // �������� ��� ������ ��������� � ������
        if (r >= rows) {
            throw std::out_of_range("�������� ������ ������");
        }
        return matrix[r];
    }

    
    void ReadFromFile(const std::string& filename) { // ������ �� �����
        std::ifstream fin(filename);
        if (!fin) {
            throw std::runtime_error("�� ������� ������� ���� ��� ������");
        }
        fin >> rows >> cols;
        matrix.resize(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                fin >> matrix[i][j];
            }
        }
    }

    
    void WriteToFile(const std::string& filename) const { // ������ � ����
        std::ofstream fout(filename);
        if (!fout) {
            throw std::runtime_error("�� ������� ������� ���� ��� ������");
        }
        fout << rows << " " << cols << "\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                fout << matrix[i][j] << " ";
            }
            fout << "\n";
        }
    }

    
    void GenerateRandomValues() { // ��������� ��������
        srand(time(0)); 
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = static_cast<T>(rand() % 100); 
            }
        }
    }

   
    void SetRandomValue(size_t r, size_t c) { // ��������� ���������� �������� � �������� �������
        if (r >= rows || c >= cols) {
            throw std::out_of_range("�������� ������");
        }
        matrix[r][c] = static_cast<T>(rand() % 100); 
    }

    
    T SumOfAverage() const { // ����� ���������, ������� �������� ��������������� �������� ����� ��������
        T sum = 0;
        size_t count = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols / 2; ++j) {
                sum = sum + matrix[i][j];
                ++count;
            }
        }
        T average = sum / count;
        T result = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (matrix[i][j] < average) {
                    result = result + matrix[i][j];
                }
            }
        }
        return result;
    }

    
    T MaxOfRowMins() const { // ���������� �������� ����� ����������� �������� �� ������ ������
        std::vector<T> rowMins(rows);
        for (size_t i = 0; i < rows; ++i) {
            rowMins[i] = *std::min_element(matrix[i].begin(), matrix[i].end());
        }
        return *std::max_element(rowMins.begin(), rowMins.end());
    }   
};