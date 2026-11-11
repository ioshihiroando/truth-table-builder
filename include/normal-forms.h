#ifndef NORMAL_FORMS_H
#define NORMAL_FORMS_H

#include <stddef.h>
#include "truth-table.h"

void print_sdnf(const TruthTable *table);

size_t check_sdnf(const TruthTable *table);

void print_sknf(const TruthTable *table);

size_t check_sknf(const TruthTable *table);

#endif