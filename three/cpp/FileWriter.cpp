#include "FileWriter.hpp"
#include <cstring> // Для memcpy
#include <iostream>
#include <unistd.h> // Для write()

FileWriter::FileWriter(BaseFile* file, IDataProcessor* processor, size_t bufferSize)
    : file(file), processor(processor), bufferSize(bufferSize) {
    buffer = new char[bufferSize]; // Выделяем память под буфер
}

FileWriter::~FileWriter() {
    delete[] buffer; // Освобождаем память
}

void FileWriter::writeData(const char* data, size_t size) {
    if (!file || !processor) return;

    size_t processedSize = processor->process(data, size, buffer, bufferSize);

    write(STDOUT_FILENO, "Обработанные данные: ", 40);
    write(STDOUT_FILENO, buffer, processedSize);
    write(STDOUT_FILENO, "\n", 1);

    file->write(buffer, processedSize);
}