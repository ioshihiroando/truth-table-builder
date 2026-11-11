#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "file.h"
#include "rpn-parser.h"
#include "variables.h"
#include "evaluator.h"

#define BLUE "\033[34m"
#define ORANGE "\033[38;5;208m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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

    printf("Формула: ");
    for (size_t i = 0; formula[i] != '\0'; i++) {
        if (formula[i] >= 'A' && formula[i] <= 'Z') {
            printf(BLUE "%c", formula[i]);
        }

        else if (formula[i] == '(' || formula[i] == ')') {
            printf(GREEN "%c", formula[i]);
        }

        else if (formula[i] == '!') {
            printf(RED "%c", formula[i]);
        }

        else {
            printf(ORANGE "%c", formula[i]);
        }
    }
    printf(RESET "\n\n");

    RPN rpn = parse_formula(formula);

    if (rpn.data == NULL) {
        printf("Ошибка составления RPN\n");
        free(formula);
        return 1;
    }

    char variables[26] = {0};
    size_t var_count = find_variables(formula, variables);

    for (size_t i = 0; i < var_count; i++) {
        printf("|" BLUE " %c " RESET, variables[i]);
    }

    printf("|" ORANGE " result " RESET "|\n");

    for (size_t i = 0; i < var_count; i++) {
        printf("|---");
    }

    printf("|--------|\n");

    int values[26];
    size_t combinations_count = (size_t) 1 << var_count;

    for (size_t i = 0; i < combinations_count; i++) {
        for (size_t j = 0; j < var_count; j++) {
            values[j] = (i >> (var_count - j - 1)) & 1;
            if (values[j] == 0) {
                printf("|" RED " 0 " RESET);
            } else {
                printf("|" GREEN " 1 " RESET);
            }
        }

        int result;

        if (evaluate_rpn(&rpn, variables, var_count, values, &result)) {
            printf("Ошибка вычисления\n");
            free(rpn.data);
            free(formula);
            return 1;
        }

        if (result == 0) {
            printf("|" RED " 0      " RESET "|\n");
        } else if (result == 1) {
            printf("|" GREEN " 1      " RESET "|\n");
        }
        
    }
    printf("\n");

    free(rpn.data);
    free(formula);
    return 0;
}
