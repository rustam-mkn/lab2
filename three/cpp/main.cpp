#include <iostream> // std
#include <cstring> // memcpy

#include "Base32Processor.hpp"
#include "RleProcessor.hpp"
#include "Base_File.hpp"
#include "DiskFile.hpp"
#include "MemoryFile.hpp"
#include "FileWriter.hpp"
#include "IDataProcessor.hpp"
#include "Base32File2.hpp"
#include "RleFile2.hpp"
#include "DoubleBase32AndRleFile.hpp"


/*
clang++ -fsanitize=address -g -std=c++11 -Ithree/hpp \
three/cpp/Base32Processor.cpp three/cpp/RleProcessor.cpp three/cpp/DiskFile.cpp \
three/cpp/MemoryFile.cpp three/cpp/FileWriter.cpp three/cpp/main.cpp -o main

lldb ./main
*/


void line() {
    std::cout << "------------------------------" << std::endl;
}

void write_int(IFile& file, int data) {
    std::cout << "Записываем целое число: " << data << std::endl;
    // Сериализуем целое число в строку (например, в ASCII)
    char buffer[sizeof(int)];
    std::memcpy(buffer, &data, sizeof(int));

    // Записываем данные в файл
    file.write(buffer, sizeof(int));
}

int main() {
    
    /**
     * Задание 3. Чисто виртуальные функции. Интерфейсы. Композиция классов.
     *
     * Наследование позволяет довольно просто переиспользовать данные и логику
     * других классов, однако зачастую этот механизм недостаточно гибкий для
     * полноценного переиспользования.
     *
     * Например, сможем ли мы в получившейся иерархии классов реализовать
     * одновременно и кодирование в base32, и сжатие при записи данных в файл?
     * Или сможем ли мы вместо записи в файл на диске делать запись в строковый
     * буфер в памяти?
     *
     * При дальнейшем рассмотрении окажется, что при помощи наследования мы
     * крепко *связали* логику преобразования данных с записью в конкретный
     * файл. Далее мы рассмотрим один из способов разделения такой логики.
     */
    line();
    // Создаем обработчики данных
    Base32Processor base32Processor;
    RleProcessor rleProcessor;

    // Создаем файлы
    DiskFile diskFile("three/txt/output_disk.txt");
    MemoryFile memoryFile(1024); // Указываем размер буфера

    // Создаем объекты FileWriter (порядок аргументов исправлен)
    FileWriter writer1(&diskFile, &base32Processor); 
    FileWriter writer2(&memoryFile, &rleProcessor);

    // Данные для записи
    const char* data = "Hello, world!";
    size_t dataSize = 13;

    // Запись данных в файлы (метод write заменен на processAndWrite, если он есть)
    writer1.writeData(data, dataSize);
    writer2.writeData(data, dataSize);


    std::cout << "Обработка и запись данных завершены" << std::endl;
    
    
    
    /**
     * Задание 3.1. Абстрактный базовый класс, чисто виртуальные функции.
     *
     * Первая проблема в нашей реализации - все наследники BaseFile будут всегда
     * обязаны непосредственно писать в файл на диске. Чтобы избавиться от этой
     * необходимости, стоит сделать базовый класс *абстрактным* в том смысле,
     * что у него не будет полей связанных с конкретным способом писать в файл.
     *
     * Создайте класс `IFile`, в котором не будет полей, но будут методы
     * `can_read`, `can_write`, `read` и `write` с такими же сигнатурами, как и
     * классе `BaseFile`. Что именно будут делать эти методы? Класс `IFile` не
     * может знать, поскольку логику этих методов будут определять наследники.
     * В этом классе эти методы не имеют реализации, и они должны быть объявлены
     * *чисто виртуальными*.
     *
     * Какие ограничения накладывает на класс наличие чисто виртуального метода?
     *
     * Получается, что в классе `IFile` есть только чисто виртуальные методы, и
     * единственная цель такого класса - определять, что должны уметь делать его
     * наследники. Совокупность действий, которые можно сделать с объектом,
     * называется его *интерфейсом*, и такие классы тоже часто называются
     * интерфейсами, отсюда берется приставка "I" в имени класса.
     *
     * Унаследуйте класс `BaseFile` от класса `IFile` и измените функцию
     * `write_int`, чтобы она работала с произвольным наследником `IFile`.
     *
     * Убедитесь, что в программе выше ничего не сломалось.
     */

    line();
    // Пример записи целого числа в файл
    int intData = 42;
    write_int(diskFile, intData);
    write_int(memoryFile, intData);

    // Пример записи строки в файл
    const char* text = "Hello, world!";
    size_t textSize = 13;
    writer1.writeData(text, textSize);
    writer2.writeData(text, textSize);

    std::cout << "Обработка и запись данных завершены" << std::endl;

    /**
     * Задание 3.2. Композиция вместо наследования.
     *
     * Реализуйте классы `Base32File2` и `RleFile2`, которые будут унаследованы
     * от класса `IFile` и в конструкторе будут получать другой объект `IFile`,
     * чьи функции они будут использовать вместо функций базового класса.
     *
     * Объекты получают объект `IFile` в виде указателя на динамически
     * выделенную память, и они ответственны за ее очищение.
     *
     * Использование объектом другого объекта в качестве поля называется
     * *композицией*.
     *
     * Проверьте, что используемые ниже объекты работают так же, как объекты
     * классов `Base32File` и `RleFile`.
     */
    line();
    {
        BaseFile* baseFile = new BaseFile("three/txt/example.txt"); // Создаем объект BaseFile, передавая путь к файлу
        Base32File2 b32f(baseFile);                                 // Создаем Base32File2, передавая указатель на объект BaseFile
        RleFile2* rf = new RleFile2(new Base32File2(new BaseFile("three/txt/example.txt"))); // Создаем RleFile2, передавая указатель на объект Base32File2

        // Пример записи целого числа
        write_int(b32f, 123456);
        write_int(*rf, 123456);

        delete rf;  // Очищаем память
    }

    /**
     * Задание 3.3. Больше композиции!
     *
     * Не реализовывая больше никаких классов, соорудите объект-наследник IFile,
     * который будет при вызове метода `write` два раза кодировать в base32,
     * после чего применять сжатие RLE и только после этого писать в файл.
     */
    line();
     {
        IFile* file = new DiskFile("three/txt/output_encoded_rle.txt"); // объект DiskFile для записи в файл

        DoubleBase32AndRleFile doubleBase32AndRleFile(file); // объект DoubleBase32AndRleFile, передавая ему DiskFile

        // запись данных в файл
        const char* data = "Hello, world!";
        size_t size = strlen(data);
        doubleBase32AndRleFile.write(data, size);

        // Очистка памяти
        delete file;

     }
 
    
    
    return 0;
}