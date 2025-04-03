#ifndef IDATAPROCESSOR_HPP
#define IDATAPROCESSOR_HPP

#include <cstddef> // Для size_t

class IDataProcessor {
public:
    virtual size_t process(const char* input, size_t inputSize, char* output, size_t outputSize) = 0;
    virtual ~IDataProcessor() {}
};

#endif // IDATAPROCESSOR_HPP
