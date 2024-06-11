#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TMatrix.h"
#include "Fraction.h"

using namespace std;


enum MenuOption { 
    SCAN_FROM_KEYBOARD = 1,
    SCAN_FROM_FILE,
    PRINT_TO_DISPLAY,
    PRINT_TO_FILE,
    GENERATE_RANDOM_VALUES,
    MODIFY_ELEMENT_CONSOLE,
    MODIFY_ELEMENT_RANDOM,
    SUM_AVERAGE,
    MAX_OF_ROW_MINS,
    EXIT_PROGRAM
};

void displayMenu() {
    cout << "Выберите пункт меню: " << endl;
    cout << SCAN_FROM_FILE << " - чтение из файла" << endl;
    cout << PRINT_TO_DISPLAY << " - вывод на экран" << endl;
    cout << PRINT_TO_FILE << " - вывод в файл" << endl;
    cout << GENERATE_RANDOM_VALUES << " - заполнить матрицу случайными значениями" << endl;
    cout << MODIFY_ELEMENT_CONSOLE << " - изменение элемента через консоль" << endl;
    cout << MODIFY_ELEMENT_RANDOM << " - изменение элемента случайным значением" << endl;
    cout << SUM_AVERAGE << " - сумма элементов, меньших среднего арифметического значений левой половины" << endl;
    cout << MAX_OF_ROW_MINS << " - наибольшее значение среди минимальных значений по каждой строке" << endl;
    cout << EXIT_PROGRAM << " - выход" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int dataTypeChoice;
    cout << "Выберите тип данных для работы с матрицей:\n1 - double\n2 - fraction\n";
    cin >> dataTypeChoice;

    if (dataTypeChoice == 1) {
        TMatrix<double> matrix; // double
        int choice;
        do {
            displayMenu();
            cin >> choice;
            switch (choice) {
            case SCAN_FROM_FILE: { // ЧТение из файла
                string path;
                cout << "Введите название файла: ";
                cin >> path;
                try {
                    matrix.ReadFromFile(path + ".txt");
                }
                catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case PRINT_TO_DISPLAY: // Вывод на экран
                cout << matrix;
                break;
            case PRINT_TO_FILE: { // Записть в Файл
                string path;
                cout << "Введите название файла: ";
                cin >> path;
                try {
                    matrix.WriteToFile(path + ".txt");
                }
                catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case GENERATE_RANDOM_VALUES: // Рандомные значения
                matrix.GenerateRandomValues();
                break;
            case MODIFY_ELEMENT_CONSOLE: { // изменить элемент матрицы руками
                size_t row, col;
                double value; 
                cout << "Введите номер строки: ";
                cin >> row;
                cout << "Введите номер столбца: ";
                cin >> col;
                cout << "Введите новое значение: ";
                cin >> value;
                try {
                    matrix(row, col) = value;
                }
                catch (const std::out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case MODIFY_ELEMENT_RANDOM: { // изменить элемент матрицы рандомом
                size_t row, col;
                cout << "Введите номер строки: ";
                cin >> row;
                cout << "Введите номер столбца: ";
                cin >> col;
                try {
                    matrix.SetRandomValue(row, col);
                }
                catch (const std::out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case SUM_AVERAGE: // сумма меньших среднего рифметического
                cout << "Сумма элементов, меньших среднего арифметического значений левой половины: "
                    << matrix.SumOfAverage() << endl;
                break;
            case MAX_OF_ROW_MINS: // Наибольшее из наименьших
                cout << "Наибольшее значение среди минимальных значений по каждой строке: "
                    << matrix.MaxOfRowMins() << endl;
                break;
            case EXIT_PROGRAM:
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } while (choice != EXIT_PROGRAM);
    }
    else if (dataTypeChoice == 2) {
        TMatrix<Fraction> matrix; // Используем тип Fraction
        int choice;
        do {
            displayMenu();
            cin >> choice;
            switch (choice) {
            case SCAN_FROM_FILE: { // ЧТение из файла
                string path;
                cout << "Введите название файла: ";
                cin >> path;
                try {
                    matrix.ReadFromFile(path + ".txt");
                }
                catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case PRINT_TO_DISPLAY: // Вывод на экран
                cout << matrix;
                break;
            case PRINT_TO_FILE: { // Запись в файл
                string path;
                cout << "Введите название файла: ";
                cin >> path;
                try {
                    matrix.WriteToFile(path + ".txt");
                }
                catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case GENERATE_RANDOM_VALUES: // Рандомные значения
                matrix.GenerateRandomValues();
                break;
            case MODIFY_ELEMENT_CONSOLE: { // изменить элемент матрицы руками
                size_t row, col;
                Fraction value; // Используем тип Fraction
                cout << "Введите номер строки: ";
                cin >> row;
                cout << "Введите номер столбца: ";
                cin >> col;
                cout << "Введите новое значение (в формате числитель/знаменатель): ";
                cin >> value;
                try {
                    matrix(row, col) = value;
                }
                catch (const std::out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case MODIFY_ELEMENT_RANDOM: { // изменить элемент матрицы рандомом
                size_t row, col;
                cout << "Введите номер строки: ";
                cin >> row;
                cout << "Введите номер столбца: ";
                cin >> col;
                try {
                    matrix.SetRandomValue(row, col);
                }
                catch (const std::out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case SUM_AVERAGE: // сумма меньших среднего рифметического
                cout << "Сумма элементов, меньших среднего арифметического значений левой половины: "
                    << matrix.SumOfAverage() << endl;
                break; 
            case MAX_OF_ROW_MINS: // Наибольшее из наименьших
                cout << "Наибольшее значение среди минимальных значений по каждой строке: "
                    << matrix.MaxOfRowMins() << endl;
                break;
            case EXIT_PROGRAM:
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } while (choice != EXIT_PROGRAM);
    }
    else {
        cout << "Неверный выбор типа данных.\n";
    }
    return 0;
}