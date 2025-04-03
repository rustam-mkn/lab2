#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include "Base_File.hpp"
#include "IDataProcessor.hpp"

class FileWriter {
private:
    BaseFile* file;
    IDataProcessor* processor;
    char* buffer; // Динамический массив вместо std::vector
    size_t bufferSize;

public:
    FileWriter(BaseFile* file, IDataProcessor* processor, size_t bufferSize = 1024);
    ~FileWriter();

    void writeData(const char* data, size_t size);
};

#endif // FILE_WRITER_HPP
