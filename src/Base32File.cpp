#include "Base32File.hpp"
#include <iostream>
#include <cstring>

Base32File::Base32File(const char* path, const char* mode, const char* table) : BaseFile(path, mode) { // путь мод таблица : вызов конструктора базового класса BaseFile
    for (int i = 0; i < 32; i++) {encode_table[i] = table[i];} // таблица table записывается в мою encode_table --- если передана полбзовательская таблица то она будет использована вместо стандартной "A..Z1..6"
    init_decode_table(); // инициализация таблицы декодирования
}

Base32File::Base32File(BaseFile& file, const char* table) : BaseFile(file) { // используем уже открытый файл [ : BaseFile(file) ]
    for (int i = 0; i < 32; i++) { encode_table[i] = table[i]; }
    init_decode_table();
}

Base32File::~Base32File() {}



// void Base32File::base32_encode(const void *data, size_t size, char *output, size_t &out_size) { // данные размер буффер ссылка на колличество записанных символов

//     const unsigned char *input = (const unsigned char *)data; // input = char *(void *data) --- приведение типов
//     out_size = 0; // размер выходных данных = 0, так как мы еще ничего не записали

//     int buffer = 0; // хранение битов чтобы потом разбить по 5
//     int bits_in_buffer = 0; // количество битов в буфере

//     for (size_t i = 0; i < size; i++) {
//         buffer = buffer << 8 | input[i]; // сдвигаем буффер на 8 бит влево и записываем input[i]
//         // buffer = 00000000 00000000 << 8 + input[0] =
//         //          00000000 01001101 << 8 + input[1] =
//         //          01001101 01100001 << 8 + input[2] =
//         //          01001101 01100001 01111010
//         bits_in_buffer += 8;

//         while (bits_in_buffer >= 5) { // если в буфере 5 или более битов, кодируем их
//             bits_in_buffer -= 5;
//             output[out_size++] = encode_table[(buffer >> bits_in_buffer) & 0x1F]; // индекс в таблице Base32 = (сдвигаем биты вправо, чтобы нужные 5 бит оказались справа & 0x1F = 00011111 --- маскируем только 5 младших бит)
//             // buffer = 01001101 01100001 01111010 
//             // bits_in_buffer = 24 --- сдвигаем на bits_in_buffer - 5 = 19 бит вправо
//             //          00000000 00000000 00001001
//             // маскируем (& 0x1F) 00001001 = 0x09 = 9
//             // 9 в encode_table[] = 'J' --- записываем 'J' в output[]

//             //buffer = 01001101 01100001 01111010
//             // bits_in_buffer = 19 - 5 = 14
//             //          00000000 00000000 00011011
//             // маскируем (& 0x1F) 00011011 = 0x1B = 27
//             // 27 в encode_table[] = '3' --- записываем '3' в output[]
//         }
//     }

//     // Обработка оставшихся битов (если их <5)
//     if (bits_in_buffer > 0) { 
//         buffer <<= (5 - bits_in_buffer); // двигаем оставшиеся биты влево
//         output[out_size++] = encode_table[buffer & 0x1F]; // кодируем в символ
//     }

//     output[out_size] = '\0'; // терминатор
// }




// Функция кодирования Base32
void Base32File::base32_encode(const void *data, size_t size, char *output, size_t &out_size) {
    if (!data || !output) {
        std::cerr << "Ошибка: передан NULL-указатель в base32_encode!\n";
        return;
    }

    out_size = 0;
    uint32_t buffer = 0;
    int bits_in_buffer = 0;

    const uint8_t* input = static_cast<const uint8_t*>(data); // кастуем к uint8_t*

    for (size_t i = 0; i < size; ++i) {
        buffer = (buffer << 8) | input[i];  
        bits_in_buffer += 8;

        while (bits_in_buffer >= 5) {
            bits_in_buffer -= 5;
            if (out_size >= MAX_OUTPUT_SIZE - 1) { 
                std::cerr << "Ошибка: превышен размер буфера в base32_encode!\n";
                return;
            }
            output[out_size++] = encode_table[(buffer >> bits_in_buffer) & 0x1F];  
        }
    }

    if (bits_in_buffer > 0) { 
        if (out_size >= MAX_OUTPUT_SIZE - 1) { 
            std::cerr << "Ошибка: превышен размер буфера в base32_encode!\n";
            return;
        }
        output[out_size++] = encode_table[(buffer << (5 - bits_in_buffer)) & 0x1F];
    }

    output[out_size] = '\0';  
}





void Base32File::encode(const void *data, size_t size, char* output, size_t& out_size) {
    base32_encode(data, size, output, out_size);
}


size_t Base32File::base32_decode(const char *encoded, size_t enc_size, char *output, size_t out_size) { // входная строка, размер строки, буфер для записи, максимальный размер выходного буфера
    int buffer = 0;
    int bits_in_buffer = 0;
    size_t out_index = 0; // позиция в выходном буфере

    for (size_t i = 0; i < enc_size; i++) {
        char c = encoded[i]; // читаем каждый символ из encoded
        if (decode_table[(unsigned char)c] == -1) continue; // проверка на недопустимые символы (пробел или \n) --> пропускаем их

        buffer = (buffer << 5) | decode_table[(unsigned char)c]; // сдвиг буффера влево на 5 бит и добавляем в buffer значение из decode_table
        bits_in_buffer += 5;

        if (bits_in_buffer >= 8) {  
            bits_in_buffer -= 8; // сдвиг на вправо на bits_in_buffer - 8 бит вправо
            if (out_index < out_size) {
                output[out_index++] = (buffer >> bits_in_buffer) & 0xFF; // 255 = 11111111
            }
        }
    }
    return out_index;
}


// Метод записи необработанных данных с кодированием в Base32
// size_t Base32File::write_raw(const void* buf, size_t size) {
//     return fwrite(buf, 1, size, get_file());
// }

size_t Base32File::write_raw(const void* buf, size_t size) {
    char encoded[2048]; // Буфер для закодированных данных
    size_t encoded_size = 0;

    base32_encode(buf, size, encoded, encoded_size); // Кодируем в Base32
    
    return fwrite(encoded, 1, encoded_size, get_file()); // Записываем Base32-строку
}



size_t Base32File::read_raw(void* buf, size_t max_bytes) {
    char encoded[2048];
    size_t encoded_size = read(encoded, sizeof(encoded) - 1);

    if (encoded_size == 0) return 0;

    encoded[encoded_size] = '\0';
    return base32_decode(encoded, encoded_size, static_cast<char*>(buf), max_bytes);
}





void Base32File::init_decode_table() {
    for (int i = 0; i < 256; i++) {
        decode_table[i] = -1; // все символы по умолчанию недопустимы
    }

    // Алфавит Base32 (поддержка обоих регистров)
    const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    const char* alphabet_lower = "abcdefghijklmnopqrstuvwxyz234567";

    for (int i = 0; i < 32; i++) {
        decode_table[(unsigned char)alphabet[i]] = i;       // большие буквы
        decode_table[(unsigned char)alphabet_lower[i]] = i; // маленькие буквы
    }
}

