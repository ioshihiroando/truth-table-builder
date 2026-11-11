#include <stdio.h>
#include "fictitious-variables.h"
#include "colors.h"

int check_fictitious_variable(
    const TruthTable *table,
    size_t *mask
) {
    for (size_t j = 0; j < table->row_count; j++) {
            if (j & *mask) {
                continue;
            }

            if (table->results[j] != table->results[j | *mask]) {
                return 0;
            }
        }
    return 1;
}

size_t find_fictitious_variables(
    const TruthTable *table,
    int *fic_var
) {
    size_t last = 0;

    for (size_t i = 0; i < table->var_count; i++) {
        size_t mask = (size_t)1 << (table->var_count - i - 1);

        if (check_fictitious_variable(table, &mask)) {
            fic_var[i] = 1;
            last = i + 1;
        }
    }

    return last;
}

void print_fictitious_variables(
    const TruthTable *table,
    const int *fictititons_variables,
    const size_t last_fictitious_variable) {
    printf("Фиктивные перменные: ");

    for (size_t i = 0; i < last_fictitious_variable; i++) {
        if (fictititons_variables[i] == 1) {
            printf(BLUE "%c" RESET, table->variables[i]);
        } else {
            continue;
        }

        if (i != (last_fictitious_variable - 1)) {
            printf(", ");
        }
    }

    printf("\n\n");
}