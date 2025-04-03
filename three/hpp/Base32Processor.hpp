#ifndef BASE32PROCESSOR_HPP
#define BASE32PROCESSOR_HPP

#include "IDataProcessor.hpp"

class Base32Processor : public IDataProcessor {
public:
    size_t process(const char* input, size_t inputSize, char* output, size_t outputSize) override;
};

#endif // BASE32PROCESSOR_HPP
