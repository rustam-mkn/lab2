#ifndef RLE_PROCESSOR_HPP
#define RLE_PROCESSOR_HPP

#include "IDataProcessor.hpp"

class RleProcessor : public IDataProcessor {
public:
    size_t process(const char* input, size_t inputSize, char* output, size_t outputSize) override;
};

#endif // RLE_PROCESSOR_HPP
