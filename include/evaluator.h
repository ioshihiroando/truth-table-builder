#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <stddef.h>
#include "rpn-parser.h"

int evaluate_rpn(
    const RPN *rpn,
    const char variables[26],
    size_t variable_count,
    const int values[26],
    int *result
);

#endif