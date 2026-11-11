#include <stdio.h>
#include <stddef.h>
#include "colors.h"
#include "normal-forms.h"

void print_sdnf(const TruthTable *table) {
    size_t last_1 = check_sdnf(table);
    if (last_1 == 0) {
        printf("Функция тождественно равна 0: невозможно построить СДНФ.\n\n");
        return;
    }

    printf("СДНФ:\n");

    for (size_t i = 0; i < last_1; i++) {
        if (table->results[i] == 0) {
            continue;
        }

        for (size_t j = 0; j < table->var_count; j++) {
            if (((i >> (table->var_count - j - 1)) & 1) == 1) {
                printf(GREEN "%c", table->variables[j]);
            } else {
                printf(RED "!%c", table->variables[j]);
            }

            if (j != (table->var_count - 1)) {
                printf(RESET " & ");
            }
        }

        if (i != (last_1 - 1)) {
            printf(RESET "  |  ");
        }
    }
    printf(RESET "\n\n");
}

size_t check_sdnf(const TruthTable *table) {
    size_t last_1 = 0;
    for (size_t i = 0; i < table->row_count; i++) {
        if (table->results[i] == 1) {
            last_1 = i + 1LLU;
        }
    }

    return last_1;
}

void print_sknf(const TruthTable *table) {
    size_t last_0 = check_sknf(table);
    if (last_0 == 0) {
        printf("Функция тождественно равна 1: невозможно построить СКНФ.\n\n");
        return;
    }

    printf("СКНФ:\n");

    for (size_t i = 0; i < last_0; i++) {
        if (table->results[i] == 1) {
            continue;
        }

        printf(RESET "(");
        for (size_t j = 0; j < table->var_count; j++) {
            if (((i >> (table->var_count - j - 1)) & 1) == 1) {
                printf(GREEN "%c", table->variables[j]);
            } else {
                printf(RED "!%c", table->variables[j]);
            }

            if (j != (table->var_count - 1)) {
                printf(RESET " | ");
            }
        }
        printf(RESET ")");

        if (i != (last_0 - 1)) {
            printf(RESET "  &  ");
        }
    }
    printf(RESET "\n\n");
}

size_t check_sknf(const TruthTable *table) {
    size_t last_0 = 0;
    for (size_t i = 0; i < table->row_count; i++) {
        if (table->results[i] == 0) {
            last_0 = i + 1LLU;
        }
    }

    return last_0;
}