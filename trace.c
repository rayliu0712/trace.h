#include "trace.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define TRACE_ARGS const char *file, const char *func, int line

typedef struct {
    const char* file;
    const char* func;
    int line;
} Trace;

static Trace* stack = NULL;
static size_t size = 0;
static size_t max_size = 128;
static const size_t step = 128;

__attribute__((destructor)) static void trace_free(void) {
    free(stack);
}

void trace_impl_push(TRACE_ARGS) {
    if (!stack) {
        stack = malloc(max_size * sizeof(Trace));
    }

    if (size == max_size) {
        max_size += step;
        stack = realloc(stack, max_size * sizeof(Trace));
    }

    stack[size].file = file;
    stack[size].func = func;
    stack[size].line = line;

    size++;
}

void trace_impl_pop(void) {
    size--;
}

void panic_impl(TRACE_ARGS, bool expr, const char* fmt, ...) {
    if (expr)
        return;

    trace_impl_push(file, func, line);

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
