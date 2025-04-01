#ifndef RLEFILE_HPP
#define RLEFILE_HPP

#include "BaseFile.hpp"
#include <iostream>
#include <cstring> // memcpy и strlen

/* Алгоритм RLE Run-Length Encoding
AAAABBBCCDAA
4A3B2C1D2A
*/


class RleFile : public BaseFile {
    public:
        RleFile(const char *path, const char *mode);  // конструктор (путь и мод)
        RleFile(const BaseFile &file);
        ~RleFile();
    
        size_t write(const void* buf, size_t n_bytes) override; // переопределяем write() для RLE-сжатия
        size_t read(void* buf, size_t max_bytes) override;  // переопределяем read() для декодирования
    
    private:
        void rle_encode(const char *input, size_t size, char *output, size_t &out_size); // кодирование
        size_t rle_decode(const char *input, size_t size, char *output, size_t max_out_size); // декодирование
    };




#endif
