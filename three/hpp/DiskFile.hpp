#ifndef DISKFILE_HPP
#define DISKFILE_HPP

#include "Base_File.hpp"
#include <fstream>

class DiskFile : public BaseFile {
private:
    const char* filename;

public:
    DiskFile(const char* filename);

    bool can_read() const override;
    bool can_write() const override;
    void read(char* buffer, size_t size) override;
    void write(const char* data, size_t size) override;
};

#endif // DISKFILE_HPP
