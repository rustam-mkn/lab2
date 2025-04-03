#include "DiskFile.hpp"
#include <fstream>
#include <iostream> // Для вывода в консоль

DiskFile::DiskFile(const char* filename) : BaseFile(""), filename(filename) {
    std::cout << "Создан объект DiskFile с файлом: " << filename << std::endl;
}

bool DiskFile::can_read() const {
    std::ifstream file(filename, std::ios::binary);
    bool result = file.good();
    std::cout << "Проверка возможности чтения из файла " << filename << ": " 
              << (result ? "Можно читать" : "Невозможно читать") << std::endl;
    return result;
}

bool DiskFile::can_write() const {
    std::ofstream file(filename, std::ios::binary | std::ios::app); // Открываем для записи
    bool result = file.good();
    std::cout << "Проверка возможности записи в файл " << filename << ": " 
              << (result ? "Можно записывать" : "Невозможно записывать") << std::endl;
    return result;
}

void DiskFile::write(const char* data, size_t size) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc); // ПЕРЕЗАПИСЬ
    if (file) {
        file.write(data, size);
        std::cout << "Данные успешно записаны в файл " << filename << std::endl;
    } else {
        std::cout << "Не удалось записать данные в файл " << filename << std::endl;
    }
}

void DiskFile::read(char* buffer, size_t size) {
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        file.read(buffer, size);
        std::cout << "Данные успешно считаны из файла " << filename << std::endl;
    } else {
        std::cout << "Не удалось прочитать данные из файла " << filename << std::endl;
    }
}
