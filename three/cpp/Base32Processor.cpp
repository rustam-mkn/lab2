#include "Base32Processor.hpp"
#include <cstring> // Для std::strlen

size_t Base32Processor::process(const char* input, size_t inputSize, char* output, size_t outputSize) {
    if (outputSize < inputSize * 2) return 0; // Проверяем, хватит ли места

    // Пример обработки: копируем и удваиваем символы (заглушка для base32)
    for (size_t i = 0, j = 0; i < inputSize && j < outputSize - 1; i++, j += 2) {
        output[j] = input[i];
        output[j + 1] = input[i];
    }
    
    return inputSize * 2; // Возвращаем новый размер данных
}
