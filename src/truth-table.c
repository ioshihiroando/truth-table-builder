#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "truth-table.h"
#include "evaluator.h"

#define BLUE "\033[34m"
#define ORANGE "\033[38;5;208m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


int build_truth_table(
    const RPN *rpn,
    const char variables[26],
    const size_t var_count,
    TruthTable *table
) {
    int values[26];
    size_t combinations_count = (size_t) 1 << var_count;

    int *results = malloc(combinations_count * sizeof(int));

    if (results == NULL) {
        return 1;
    }
    
    table->row_count = combinations_count;
    table->results = results;

    for (size_t i = 0; i < combinations_count; i++) {
        for (size_t j = 0; j < var_count; j++) {
            values[j] = (i >> (var_count - j - 1)) & 1;
        }

        if (evaluate_rpn(rpn, variables, var_count, values, &results[i])) {
            printf("Ошибка вычисления\n");
            return 1;
        }        
    }

    return 0;
}

void print_truth_table(
    const TruthTable *table, 
    const char *formula
) {
    // выводим формулу
    printf("\nФормула: ");
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

    // строим таблицу истинности
    for (size_t i = 0; i < table->var_count; i++) {
        printf("|" BLUE " %c " RESET, table->variables[i]);
    }

    printf("|" ORANGE " result " RESET "|\n");

    for (size_t i = 0; i < table->var_count; i++) {
        printf("|---");
    }

    printf("|--------|\n");

    int values[26];

    for (size_t i = 0; i < table->row_count; i++) {
        for (size_t j = 0; j < table->var_count; j++) {
            values[j] = (i >> (table->var_count - j - 1)) & 1;
            if (values[j] == 0) {
                printf("|" RED " 0 " RESET);
            } else {
                printf("|" GREEN " 1 " RESET);
            }
        }

        if (table->results[i] == 0) {
            printf("|" RED " 0      " RESET "|\n");
        } else if (table->results[i] == 1) {
            printf("|" GREEN " 1      " RESET "|\n");
        }
        
    }
    printf("\n");
}