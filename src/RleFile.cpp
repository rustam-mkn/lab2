#include "RleFile.hpp"
#include <iostream>
#include <cstring>

RleFile::RleFile(const char *path, const char *mode) : BaseFile(path, mode) { // Вызов конструктора BaseFile для открытия файла
    //std::cout << "создан RleFile: " << path << std::endl;
}

RleFile::RleFile(const BaseFile &base) : BaseFile(base) {
    //std::cout << "RleFile создан из существующего файла" << std::endl;
}

RleFile::~RleFile() {
    // НЕ вызываем close(), BaseFile сам это делает
}




// Переопределяем write(), чтобы оно сжимало данные перед записью
size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!is_open()) return 0;
    std::cout << std::endl;

    char encoded[1024];  // Буфер для сжатых данных
    size_t encoded_size = 0;

    rle_encode((const char*)buf, n_bytes, encoded, encoded_size); // Кодируем данные

    // Вывод сжатых данных в консоль
    std::cout << "Сжатые данные: \n";
    for (size_t i = 0; i < encoded_size; i++) {
        std::cout << "[" << (unsigned int)(unsigned char)encoded[i] << "]";
    }
    std::cout << std::endl;

    std::cout << n_bytes << " байт" << " --> " << encoded_size << " байт" << std::endl;

    return BaseFile::write(encoded, encoded_size);  // Записываем в файл уже сжатые данные
}

// Переопределяем read(), чтобы оно декодировало данные после чтения
size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!is_open()) return 0;

    char encoded[1024];  
    size_t encoded_size = BaseFile::read(encoded, sizeof(encoded) - 1);  // Читаем закодированные данные
    if (encoded_size == 0) return 0;

    return rle_decode(encoded, encoded_size, (char*)buf, max_bytes); // Декодируем и возвращаем размер
}


// Алгоритм RLE сжатия
void RleFile::rle_encode(const char *input, size_t size, char *output, size_t &out_size) {
    out_size = 0;
    for (size_t i = 0; i < size; ) {
        char current = input[i];
        size_t count = 1;

        while (i + count < size && input[i + count] == current && count < 255) { 
            count++;
        }

        output[out_size++] = count;  
        output[out_size++] = current;  
        i += count;
    }
}

// Алгоритм RLE декодирования
size_t RleFile::rle_decode(const char *input, size_t size, char *output, size_t max_out_size) {
    size_t out_size = 0;
    for (size_t i = 0; i < size; i += 2) {
        unsigned char count = input[i];
        char value = input[i + 1];

        if (out_size + count > max_out_size) break;
        

        for (unsigned char j = 0; j < count; j++) {
            output[out_size++] = value;
        }
    }
    return out_size;
}

