#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>

void clear();
template<typename T>
void input_positive(T& var);

// Реализация шаблонной функции должна быть в заголовочном файле
template<typename T>
void input_positive(T& var) {
    while (!(std::cin >> var) || var <= 0) {
        clear();
        std::cout << "Invalid input. Enter positive number: ";
    }
    clear();
}

#endif