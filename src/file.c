#include <stdio.h>
#include <stdlib.h>
#include "file.h"

char *read_file (const char *path) {
    // открываем файл
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return NULL;
    }

    size_t capacity = 8;
    size_t count_sym = 0;
    char *data = calloc(capacity, sizeof(char));

    if (data == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        return NULL;
    }

    int sym;
    while ((sym = fgetc(file)) != EOF) {
        if ((char)sym == ' ') {
            continue;
        }

        if (capacity == count_sym) {
            capacity *= 2;

            char *temp = realloc(data, capacity);

            if (temp == NULL) {
                printf("Ошибка перераспределения памяти\n");
                free(data);
                fclose(file);
                return NULL;
            }

            data = temp;
        }

        if ('a' <= sym && sym <= 'z') {
            sym -= 32;
        }

        data[count_sym] = (char)sym;
        count_sym++;
    }

    data[count_sym] = '\0';
    // закрываем файл
    fclose(file);
    return data;
}