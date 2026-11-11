#ifndef FICTITIOUS_VARIABLES_H
#define FICTITIOUS_VARIABLES_H

#include "truth-table.h"

size_t find_fictitious_variables(
    const TruthTable *table,
    int *fic_var
);

void print_fictitious_variables(
    const TruthTable *table,
    const int *fictititons_variables,
    const size_t last_fictitious_variable);

#endif