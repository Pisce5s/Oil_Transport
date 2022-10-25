#pragma once
#include <iostream>

template <typename T>
T get_pozitive_number(T min, T max)
{
    T x;
    while ((std::cin >> x).fail() || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка, введите подходящее число\n";
    }
    return x;
}