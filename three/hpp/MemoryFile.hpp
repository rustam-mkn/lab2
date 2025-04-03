#ifndef MEMORYFILE_HPP
#define MEMORYFILE_HPP

#include "Base_File.hpp"

class MemoryFile : public BaseFile {
private:
    char* memoryBuffer;
    size_t bufferSize;

public:
    MemoryFile(size_t size);
    ~MemoryFile();

    bool can_read() const override;
    bool can_write() const override;
    void read(char* buffer, size_t size) override;
    void write(const char* data, size_t size) override;
};

#endif // MEMORYFILE_HPP
