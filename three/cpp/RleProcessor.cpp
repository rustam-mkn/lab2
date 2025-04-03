#include "RleProcessor.hpp"

size_t RleProcessor::process(const char* input, size_t inputSize, char* output, size_t outputSize) {
    if (outputSize < inputSize) return 0; // Проверка на размер

    size_t j = 0;
    for (size_t i = 0; i < inputSize && j < outputSize - 2; i++) {
        char currentChar = input[i];
        size_t count = 1;

        while (i + 1 < inputSize && input[i + 1] == currentChar && count < 255) {
            count++;
            i++;
        }

        output[j++] = currentChar;
        output[j++] = static_cast<char>(count);
    }

    return j; // Новый размер
}
