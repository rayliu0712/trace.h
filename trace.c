#define _POSIX_C_SOURCE 200809L
#include "trace.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACE const char *file, const char *func, int line

typedef struct {
    char* file;
    char* func;
    int line;
} Trace;

static Trace* stack = NULL;
static size_t size = 0;
static size_t max_size = 128;
static const size_t step = 128;

__attribute__((destructor)) static void trace_free(void) {
    while (size)
        trace_pop();
    free(stack);
}

void trace_push(TRACE) {
    if (!stack) {
        stack = malloc(max_size * sizeof(Trace));
    }

    if (size == max_size) {
        max_size += step;
        stack = realloc(stack, max_size * sizeof(Trace));
    }

    stack[size].file = strdup(file);
    stack[size].func = strdup(func);
    stack[size].line = line;

    size++;
}

void trace_pop(void) {
    size--;
    free(stack[size].file);
    free(stack[size].func);
}

void panic_impl(TRACE, bool expr, const char* fmt, ...) {
    if (expr)
        return;

    trace_push(file, func, line);

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

    exit(EXIT_FAILURE);
}
