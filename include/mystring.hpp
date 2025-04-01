#ifndef MYSTRING_HPP
#define MYSTRING_HPP

#include <cstddef> // size_t

class MyString {
private:
    char *data;  // Указатель на динамическую память для строки
    size_t length; // Длина строки

public:
    // Конструкторы
    MyString(); // пустая строка
    MyString(const char *str); // Инициализация строкой

    // Деструктор
    ~MyString();

    // Операции с элементами
    char get(int i) const; // Получение символа по индексу
    void set(int i, char c); // Установка символа по индексу

    // Операции со строкой
    void set_new_string(const char *str); // Замена содержимого
    void print() const; // Печать строки
    void read_line(); // Чтение строки с консоли
};

void line();

#endif
