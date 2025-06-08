#include "trace.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLNULL ((void**)0)

typedef struct {
    char* file;
    char* func;
    int line;
} Trace;

Trace* stack = NULL;
size_t size = 0;
size_t max_size = 128;
const size_t step = 128;

void* trace_init_impl(void) {
    stack = malloc(max_size * sizeof(Trace));
    return NULL;
}

static void check_init(void) {
    if (!stack) {
        fprintf(stderr, "\n[ERROR] You forgot to trace_init()\n");
        exit(EXIT_FAILURE);
    }
}

void trace_free(void**) {
    check_init();

    while (size)
        untrace(NULLNULL);
    free(stack);
}

void* trace_impl(TRACE) {
    check_init();

    if (size == max_size) {
        max_size += step;
        stack = realloc(stack, max_size);
    }

    size_t file_len = strlen(trace_file) + 1;
    stack[size].file = malloc(file_len);
    strncpy(stack[size].file, trace_file, file_len);

    size_t func_len = strlen(trace_func) + 1;
    stack[size].func = malloc(func_len);
    strncpy(stack[size].func, trace_func, func_len);

    stack[size].line = trace_line;

    size++;

    return NULL;
}

void untrace(void**) {
    check_init();

    size--;
    free(stack[size].file);
    free(stack[size].func);
}

void panic_impl(TRACE, bool expr, const char* fmt, ...) {
    check_init();
    if (expr)
        return;

    trace_impl(trace_file, trace_func, trace_line);

    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "\n[ERROR] ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    for (size_t i = 0; i < size; i++) {
        fprintf(stderr, "\n[FILE] %s\n", stack[i].file);
        fprintf(stderr, "[FUNC] %s()\n", stack[i].func);
        fprintf(stderr, "[LINE] %d\n", stack[i].line);
    }

    va_end(args);

    trace_free(NULLNULL);
    exit(EXIT_FAILURE);
}
