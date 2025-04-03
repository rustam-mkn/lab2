#include "MemoryFile.hpp"
#include <cstring> // Для memcpy
#include <iostream>

MemoryFile::MemoryFile(size_t capacity) 
    : BaseFile("memory"), memoryBuffer(new char[capacity]), bufferSize(capacity) {
    std::cout << "Создан объект MemoryFile с размером буфера: " << capacity << std::endl;
}

MemoryFile::~MemoryFile() {
    delete[] memoryBuffer;
    std::cout << "Память, занятая объектом MemoryFile, очищена." << std::endl;
}

bool MemoryFile::can_read() const {
    return true; // Память всегда доступна для чтения
}

bool MemoryFile::can_write() const {
    return true; // Память всегда доступна для записи
}

void MemoryFile::write(const char* data, size_t size) {
    std::memcpy(memoryBuffer, data, size);
    std::cout << "Записано " << size << " байт в память." << std::endl;
}

void MemoryFile::read(char* buffer, size_t size) {
    std::memcpy(buffer, memoryBuffer, size);
    std::cout << "Прочитано " << size << " байт из памяти." << std::endl;
}
