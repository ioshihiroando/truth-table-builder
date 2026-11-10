#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "file.h"
#include "rpn-parser.h"
#include "variables.h"

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

    RPN rpn = parse_formula(formula);

    if (rpn.data == NULL) {
        printf("Ошибка составления RPN\n");
        free(formula);
        return 1;
    }

    char variables[26] = {0};
    size_t var_count = find_variables(formula, variables);

    printf("%s\n", formula);
    printf("%s\n", rpn.data);
    printf("%s\n", variables);
    printf("%zu\n", var_count);

    free(rpn.data);
    free(formula);
    return 0;
}
