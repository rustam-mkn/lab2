#include "function.hpp"


// в этой функции мы работаем с объектом, который уже был создан в другом месте [BaseFile]
// мы можем обращаться к методам этого класса тк объект передан по ссылке
void write_int(BaseFile& file, int number) { // из BaseFile& file у меня есть доступ к методам класса BaseFile [public]
    char buffer[12]; // буфер для числа
    int len = 0;    

    if (number < 0) { 
        file.write_raw("-", 1);  // записываем минус
        number = -number;
    }

    do {                                    // разбиение числа на отдельные цифры
        buffer[len++] = '0' + (number % 10);// '0' = 48 в ASCII. 48 + 3 = 51 --- 51 = '3'
        number /= 10; // переход к следующей цифре
    } while (number > 0);

    for (int i = len - 1; i >= 0; i--) {
        file.write_raw(&buffer[i], 1);  // запись в обратном порядке
    }

    file.write_raw("\n", 1); // Перенос строки
    std::cout << "Записано число в файл.\n";
}

// Чтение числа из файла и вывод на экран
void read_int(BaseFile& file) {
    char buffer[12] = {0}; // Буфер для чтения
    int bytes_read = file.read_raw(buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Завершающий символ
        std::cout << "Прочитано из файла: " << buffer; // Вывод строки из файла
    } else {
        std::cout << "Ошибка чтения файла.\n";
    }
}







