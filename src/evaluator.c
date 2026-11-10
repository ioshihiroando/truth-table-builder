#include <stddef.h>
#include <stdlib.h>
#include "rpn-parser.h"

int evaluate_rpn(
    const RPN *rpn,
    const char variables[26],
    size_t variable_count,
    const int values[26],
    int *result
) {
    int *stack = malloc(rpn->length * sizeof(int));

    if (stack == NULL) {
        return 1;
    }

    size_t stack_size = 0;

    for (size_t i = 0; i < rpn->length; i++) {
        char current = rpn->data[i];

        if (current >= 'A' && current <= 'Z') {
            size_t j = 0;
            while (j < variable_count && current != variables[j]) {
                j++;
            }

            if (j == variable_count) {
                free(stack);
                return 1;
            }
            
            stack[stack_size++] = values[j];
        }

        else if (current == '0' || current == '1') {
            stack[stack_size++] = current - '0';
        }

        else {
            if (stack_size == 0) {
                free(stack);
                return 1;
            }

            if (current == '!') {
                stack[stack_size - 1] = !stack[stack_size - 1];
            }

            else if (stack_size <  2) {
                free(stack);
                return 1;
            }

            else if (current == '&') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];

                stack[stack_size++] = left && right;
            }

            else if (current == '|') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = left || right;
            }

            else if (current == '^') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = left != right;
            }

            else if (current == '>') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = left <= right;
            }

            else if (current == '<') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = left > right;
            }

            else if (current == '#') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = !(left || right);
            }

            else if (current == '/') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = !(left && right);
            }

            else if (current == '=') {
                int right = stack[stack_size-- - 1];
                int left = stack[stack_size-- - 1];
                
                stack[stack_size++] = left == right;
            }
        }
    }

    if (stack_size != 1) {
        free(stack);
        return 1;
    }

    *result = stack[0];

    free(stack);
    return 0;
}