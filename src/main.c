#include <stdio.h>
#include "file.h"

/*
! - Инверсия
| - Дизъюнкция
& - Конъюнкция
^ - Сложение по модулю 2 (xor)
= - Эквивалентность
> - Импликация
< - Коимпликация
# - Стрелка Пирса
/ - Штрих Шеффера
*/

int main(int argc, char *argv[]) {
    /*
    argc - количество аргументов командной строки
    argv - массив значений аргументов командной строки
    */
    if (argc < 2) {
        printf("Укажите путь к файлу\n");
        return 1;
    }

    char *formula = read_file(argv[1]);

    if (formula == NULL) {
        printf("Ошибка чтения файла\n");
        return 1;
    }

    printf("%s", formula);

    return 0;
}
