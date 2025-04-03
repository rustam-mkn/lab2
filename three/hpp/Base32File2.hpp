#ifndef BASE32FILE2_HPP
#define BASE32FILE2_HPP

#include "IFile.hpp"

class Base32File2 : public IFile {
private:
    IFile* file; // Указатель на объект IFile, который будет использоваться

public:
    Base32File2(IFile* file) : file(file) {}

    bool can_read() const override {
        return file->can_read();
    }

    bool can_write() const override {
        return file->can_write();
    }

    void read(char* buffer, size_t size) override {
        file->read(buffer, size);
    }

    void write(const char* data, size_t size) override {
        file->write(data, size);
    }

    ~Base32File2() {
        delete file;  // Удаляем объект, переданный в конструктор
    }
};

#endif // BASE32FILE2_HPP
