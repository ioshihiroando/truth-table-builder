#ifndef RPN_PARSER_H
#define RPN_PARSER_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} RPN;

typedef struct {
    const char *formula;
    size_t position;
    RPN rpn;
} Parser;

RPN parse_formula(const char *formula);

#endif
