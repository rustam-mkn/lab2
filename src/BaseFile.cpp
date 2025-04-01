#include "BaseFile.hpp"


BaseFile::BaseFile() : file(nullptr) {
    std::cout << "BaseFile: конструктор по умолчанию\n"; // конструктор по умолчанию
    filename[0] = '\0'; // пустая строка
}

BaseFile::BaseFile(const char* path, const char* mode) { // конструктор path, mode
    file = fopen(path, mode); // open file

    // Сохраняем имя файла
    strncpy(filename, path, sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0';

    std::cout << "'" << filename << "', '" << mode << "'" << std::endl;

    if (!file) {std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'!" << std::endl;}
}


BaseFile::BaseFile(FILE* exFile) : file(exFile) {
    std::cout << "BaseFile: конструктор (FILE*)\n";
    if (!file) {std::cerr << "Ошибка: передан nullptr в конструктор BaseFile(FILE*)!\n";};
}

BaseFile::~BaseFile() {
    if (file) {
        std::cout << "~: Закрываю файл '" << filename << "'" << std::endl;
        fclose(file);
        file = nullptr;
    } else {
        std::cerr << "Ошибка: попытка повторного закрытия файла '" << filename << "'!" << std::endl;
    }
}


bool BaseFile::is_open() const {
    return file != nullptr;
}

bool BaseFile::can_read() const {
    if (file == nullptr) return false; 

    int c = fgetc(file); // считывает 1 символ (содержит ASCII код)
    if (c == EOF) return false; // если ошибка или конец файла (EOF = End Of File = -1)

    ungetc(c, file); // возвращаем символ обратно
    return true;
}

bool BaseFile::can_write() const {
    if (file == nullptr) return false;
    
    char text = 'x'; // для попытки записать
    if (fwrite(&text, 1, 1, file) != 1) return false; // тестируем возможность записи (fwrite записывает 1 байт в файл)
    
    fseek(file, -1, SEEK_CUR); // (SEEK_CUR = отменяем запись относительно текущей позиции)
    return true;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    return file ? fwrite(buf, 1, n_bytes, file) : 0; // теранар
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes) {
    return file ? fread(buf, 1, max_bytes, file) : 0;
}

long BaseFile::tell() { // позволяет узнать текущую позицию в файле
    if (!file) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) { // перемещает в позицию offset
    if (!file) return false;
    return fseek(file, offset, SEEK_SET) == 0; // SEEK_SET = offset считается от начала файла
}





// запись в файл без передачи памяти
bool newText::write_text(const char* text) {
    return write_raw(text, strlen(text)) == strlen(text);
}

bool newText::read_text(char *buf, size_t max_bytes) {
    size_t r = read_raw(buf, max_bytes);
    
    if (r > 0) {
        buf[r] = '\0'; // ставим `\0` в конец строки
        return true;
    }
    
    buf[0] = '\0'; // защита от мусора, если ничего не считалось
    return false;
}

newText::~newText() {
}


size_t BaseFile::write(const void* buf, size_t n_bytes) {
    if (!is_open()) return 0;  
    return fwrite(buf, 1, n_bytes, file); // побеждена рекурсия (это был пиздец)
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return file ? fread(buf, 1, max_bytes, file) : 0; // устранена [ИСКЛЮЧЕНА] рекурсия
}


FILE* BaseFile::get_file() const {
    return file;
}




void BaseFile::close() {
    if (file) {
        fclose(file);
        file = nullptr;
    }
}



