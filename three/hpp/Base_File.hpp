#ifndef BASE_FILE_HPP
#define BASE_FILE_HPP

#include "IFile.hpp"
#include <fstream>

class BaseFile : public IFile {
private:
    const char* filename; // Имя файла

public:
    BaseFile(const char* filename) : filename(filename) {}

    bool can_read() const override {
        std::ifstream file(filename);
        return file.is_open();
    }

    bool can_write() const override {
        std::ofstream file(filename, std::ios::app);
        return file.is_open();
    }

    void read(char* buffer, size_t size) override {
        std::ifstream inFile(filename, std::ios::binary);
        if (inFile.is_open()) {
            inFile.read(buffer, size);
            inFile.close();
        }
    }

    void write(const char* data, size_t size) override {
        std::ofstream outFile(filename, std::ios::binary | std::ios::app);
        if (outFile.is_open()) {
            outFile.write(data, size);
            outFile.close();
        }
    }

    ~BaseFile() {}
};

#endif // BASE_FILE_HPP
