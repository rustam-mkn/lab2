// DoubleBase32AndRleFile.hpp
#ifndef DOUBLEBASE32ANDRLEFILE_HPP
#define DOUBLEBASE32ANDRLEFILE_HPP

#include "IFile.hpp"
#include "Base32Processor.hpp"
#include "RleProcessor.hpp"
#include "DiskFile.hpp" // Или MemoryFile в зависимости от потребности

class DoubleBase32AndRleFile : public IFile {
private:
    IFile* file;  // Объект, в который будем записывать результат
    Base32Processor base32Processor;  // Объект для кодирования Base32
    RleProcessor rleProcessor;  // Объект для сжатия с помощью RLE

public:
    DoubleBase32AndRleFile(IFile* file) : file(file) {}

    bool can_read() const override {
        return file->can_read();  // Используем метод can_read() из переданного объекта
    }

    bool can_write() const override {
        return file->can_write();  // Используем метод can_write() из переданного объекта
    }

    void write(const char* data, size_t size) override {
        // Первый этап: кодирование в Base32
        size_t base32Size = size * 2; // Примерный размер после кодирования
        char* base32Encoded = new char[base32Size];
        base32Size = base32Processor.process(data, size, base32Encoded, base32Size);

        // Второй этап: кодирование в Base32 снова
        size_t base32Size2 = base32Size * 2; // Размер после второго кодирования
        char* base32Encoded2 = new char[base32Size2];
        base32Size2 = base32Processor.process(base32Encoded, base32Size, base32Encoded2, base32Size2);

        // Третий этап: сжатие с использованием RLE
        size_t rleSize = base32Size2 * 2; // Примерный размер после сжатия
        char* compressedData = new char[rleSize];
        rleSize = rleProcessor.process(base32Encoded2, base32Size2, compressedData, rleSize);

        // Записываем сжатые данные в файл
        file->write(compressedData, rleSize);

        // Очистка памяти
        delete[] base32Encoded;
        delete[] base32Encoded2;
        delete[] compressedData;
    }

    void read(char* buffer, size_t size) override {
        file->read(buffer, size);  // Просто передаем вызов в основной файл
    }
};

#endif // DOUBLEBASE32ANDRLEFILE_HPP
