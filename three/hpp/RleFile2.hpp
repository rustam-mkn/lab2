#ifndef RLEFILE2_HPP
#define RLEFILE2_HPP

#include "IFile.hpp"
#include "RleProcessor.hpp"

class RleFile2 : public IFile {
private:
    IFile* file;  // Указатель на объект IFile

public:
    RleFile2(IFile* file) : file(file) {}  // Инициализация через конструктор

    ~RleFile2() {
        delete file;  // Освобождаем память, переданную в конструктор
    }

    bool can_read() const override {
        return file->can_read();  // Делаем делегирование
    }

    bool can_write() const override {
        return file->can_write();  // Делаем делегирование
    }

    void read(char* buffer, size_t size) override {
        file->read(buffer, size);  // Делаем делегирование
    }

    void write(const char* data, size_t size) override {
        // Дополнительная обработка данных с использованием RleProcessor
        RleProcessor processor;
        char* processedData = new char[size];  // Выделение памяти для обработанных данных
        size_t processedSize = processor.process(data, size, processedData, size);

        file->write(processedData, processedSize);  // Запись в файл
        delete[] processedData;  // Освобождение памяти после записи
    }
};

#endif // RLEFILE2_HPP
