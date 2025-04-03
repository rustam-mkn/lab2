#ifndef IFILE_HPP
#define IFILE_HPP

#include <cstddef> // Для size_t

class IFile {
public:
    // Чисто виртуальные функции
    virtual bool can_read() const = 0; // Может ли файл быть прочитан
    virtual bool can_write() const = 0; // Может ли файл быть записан
    virtual void read(char* buffer, size_t size) = 0; // Чтение из файла
    virtual void write(const char* data, size_t size) = 0; // Запись в файл

    virtual ~IFile() {} // Виртуальный деструктор
};

#endif // IFILE_HPP
