#include "mystring.hpp"
#include <iostream>
#include <cstring>

MyString::MyString() : data(nullptr), length(0) {}

MyString::MyString(const char *str) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1]; // +1 для нулевого символа
        std::strcpy(data, str); // Копируем строку
    } else {
        data = nullptr;
        length = 0;
    }
}

MyString::~MyString() {
    delete[] data; // Освобождаем динамическую память
}

char MyString::get(int i) const {
    if (i >= 0 && static_cast<size_t>(i) < length) {
        return data[i];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void MyString::set(int i, char c) {
    if (i >= 0 && static_cast<size_t>(i) < length) {
        data[i] = c;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void MyString::set_new_string(const char *str) {
    if (str) {
        delete[] data; // Освобождаем старую память, если есть

        length = std::strlen(str);
        data = new char[length + 1]; // +1 для нулевого символа
        std::strcpy(data, str); // Копируем новую строку
    } else {
        delete[] data;
        data = nullptr;
        length = 0;
    }
}

void MyString::print() const {
    if (data) {
        std::cout << data << std::endl;
    } else {
        std::cout << "(empty)" << std::endl;
    }
}

void MyString::read_line() {
    char buffer[1024]; // Буфер для ввода строки
    std::cin.getline(buffer, sizeof(buffer));

    set_new_string(buffer); // Устанавливаем новую строку
}

void line() {
    std::cout << "------------------------------" << std::endl;
}
