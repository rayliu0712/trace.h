#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

#define TRACE_ARGS const char *file, const char *func, int line

#define GET_TRACE __FILE__, __func__, __LINE__

//
// trace

void trace_impl_push(TRACE_ARGS);

void trace_impl_pop(void);

#define TRACE(expr)                 \
    do {                            \
        trace_impl_push(GET_TRACE); \
        (expr);                     \
        trace_impl_pop();           \
    } while (0)

//
// panic

void panic_impl(TRACE_ARGS, bool expr, const char* fmt, ...);

#define PANIC(expr, msg) panic_impl(GET_TRACE, (expr), (msg));

#define PANIC_F(expr, fmt, ...) panic_impl(GET_TRACE, (expr), (fmt), __VA_ARGS__)

#define PANIC_NULL(ptr) PANIC_F((ptr), "pointer \"%s\" is NULL", #ptr)

#undef TRACE_ARGS

#endif
