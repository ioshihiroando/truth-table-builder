#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include <stddef.h>
#include "rpn-parser.h"

typedef struct {
    char *variables;
    size_t var_count;

    size_t row_count;
    int *results;
} TruthTable;

int build_truth_table(
    const RPN *rpn,
    const char variables[26],
    const size_t var_count,
    TruthTable *table
);

void print_truth_table(
    const TruthTable *table,
    const char *formula
);

void free_truth_table(TruthTable *table);

#endif