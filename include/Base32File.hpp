#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP

#include "BaseFile.hpp"
#include <cstring> // memcpy и strlen

/*
класс должен кодировать данные в Base32 при записи в файл
декодировать данные из Base32 при чтении из файла
позволять пользователю указать таблицу кодировки (по умолчанию "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456")

Base32 — это метод кодирования данных, который превращает каждые 5 бит исходных данных в 1 символ
из 32-символьного алфавита

01001101 01100001 01111010 01101001 01101110 01100111   кодируем по 5 бит:
01001 10110 00010 11110 10011 01001 10110 01100         кодируем с таблицей A..Z1..6:
"K7CZNZG"

при декодировании процесс обратный
*/

const size_t MAX_OUTPUT_SIZE = 1024; // максимальный размер буфера вывода


class Base32File : public BaseFile {
private:
    char encode_table[32]; // таблица символов Base32 (по умолчанию "A..Z1..6")
    char decode_table[256]; // обратная таблица --- можно быстро найти индекс каждого символа
    void init_decode_table(); // инициализация таблицы декодирования (заполняет decode_table)
    // decode_table['A'] == 0
    // decode_table['6'] == 31
    // остальные символы == -1

    
    
    void base32_encode(const void *data, size_t size, char *output, size_t &out_size); // кодирует данные в Base32
    size_t base32_decode(const char *encoded, size_t enc_size, char *output, size_t out_size); // декодирует
    
public:
    Base32File(const char* path, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(BaseFile& file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File();

    void encode(const void *data, size_t size, char* output, size_t& out_size); // кодирование данных


    // override – указывает, что метод переопределяет [ virtual ] функцию из базового класса
    // override можно применять только к виртуальным функциям
    size_t write_raw(const void* buf, size_t n_bytes) override; // переопределение базовых функций
    size_t read_raw(void* buf, size_t max_bytes) override;      // override нужен для безопасности, от ошибок в переопределении
    // для переопределения должна совпадать (сигнатура): одинаковые аргументы

    




};









#endif