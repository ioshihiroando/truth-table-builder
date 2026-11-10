#include "variables.h"
#include <stddef.h>

size_t find_variables(const char *formula, char variables[26]) {
    int found[26] = {0};

    for (size_t i = 0; formula[i] != '\0'; i++) {
        char current = formula[i];

        if (current >= 'A' && current <= 'Z') {
            found[current - 'A'] = 1;
        }
    }

    size_t count = 0;

    for (int i = 0; i < 26; i++) {
        if (found[i]) {
            variables[count] = 'A' + i;
            count++;
        }
    }

    return count;
}