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
    std::vector<std::vector<T>> matrix; // Вектор чтобы хранить матрицу
    size_t rows, cols; // размер матрицы

public:
    TMatrix() : rows(0), cols(0) {} // Конструктор по умолчанию
    TMatrix(size_t r, size_t c) : rows(r), cols(c), matrix(r, std::vector<T>(c)) {} // Конструктор с параметрами

   
    T& operator()(size_t r, size_t c) {  // Оператор доступа для модификации элемента
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Неверный индекс");
        }
        return matrix[r][c];
    }

    // Перегрузки
    
    const T& operator()(size_t r, size_t c) const { // Оператор для чтения элемента
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Неверный индекс");
        }
        return matrix[r][c];
    }

    friend std::ostream& operator<<(std::ostream& os, const TMatrix& m) { // Оператор вывода для класса TMatrix
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j) {
                os << m(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }

    const std::vector<T>& operator[](size_t r) const { // Оператор для чтения элементов в строке
        if (r >= rows) {
            throw std::out_of_range("Неверный индекс строки");
        }
        return matrix[r];
    }

    
    void ReadFromFile(const std::string& filename) { // Чтение из файла
        std::ifstream fin(filename);
        if (!fin) {
            throw std::runtime_error("Не удалось открыть файл для чтения");
        }
        fin >> rows >> cols;
        matrix.resize(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                fin >> matrix[i][j];
            }
        }
    }

    
    void WriteToFile(const std::string& filename) const { // Запись в файл
        std::ofstream fout(filename);
        if (!fout) {
            throw std::runtime_error("Не удалось открыть файл для записи");
        }
        fout << rows << " " << cols << "\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                fout << matrix[i][j] << " ";
            }
            fout << "\n";
        }
    }

    
    void GenerateRandomValues() { // Рандомные значения
        srand(time(0)); 
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = static_cast<T>(rand() % 100); 
            }
        }
    }

   
    void SetRandomValue(size_t r, size_t c) { // Установка рандомного значения в заданный элемент
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Неверный индекс");
        }
        matrix[r][c] = static_cast<T>(rand() % 100); 
    }

    
    T SumOfAverage() const { // Сумма элементов, меньших среднего арифметического значений левой половины
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

    
    T MaxOfRowMins() const { // Наибольшее значение среди минимальных значений по каждой строке
        std::vector<T> rowMins(rows);
        for (size_t i = 0; i < rows; ++i) {
            rowMins[i] = *std::min_element(matrix[i].begin(), matrix[i].end());
        }
        return *std::max_element(rowMins.begin(), rowMins.end());
    }   
};