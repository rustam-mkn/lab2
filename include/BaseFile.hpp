#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio> // FILE, fopen, fclose, fread, fwrite
#include <cstring>
#include <iostream>

/*
Функция fopen() возвращает FILE*, если файл открылся успешно, иначе nullptr
FILE* f = fopen("example.txt", "w");    | w = запись (write)
                                        | r = чтение (read)          
                                        | a
FILE* указывает на динамически созданный ресурс, который нужно явно закрывать (fclose)
*/


class BaseFile {
protected:
    char filename[256]; // массив для красивого вывода пути файла в деструкторе (и не только)
    
private:
    FILE* file; // указатель на файл --- nullptr [файл не открыт] / указатель на структуру FILE [файл открыт]

public:
    BaseFile(); // конструктор по умолчанию --- nullptr [ : file(nullptr) {}]

    BaseFile(const char* path, const char* mode); // open file по пути (path) в моде (mode)
    
    BaseFile(FILE* exFile); // использование открытого файла

    virtual ~BaseFile(); // мне нужен был виртуал чтобы изменить базовый метод в производном классе

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;
    virtual size_t write_raw(const void *buf, size_t n_bytes); // virtual - разрешение на переопределение в наследственном классе
    virtual size_t read_raw(void *buf, size_t max_bytes);
    long tell(); // текущая позиция в файле
    bool seek(long offset); // перемещает указатель
    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);

    FILE* get_file() const; // для получения указателя на FILE*
    
    void close();
    
};







class newText : public BaseFile {
public:
    newText(const char *path, const char *mode) : BaseFile(path, mode) {} // наследование

    newText(BaseFile &base) : BaseFile(base) {}

    ~newText();

    bool write_text(const char* text);
    bool read_text(char *buf, size_t max_bytes);
};



#endif // BASEFILE_HPP
