#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

#define TRACE const char *file, const char *func, int line

#define GET_TRACE __FILE__, __func__, __LINE__

//
// trace

void trace_push(TRACE);

void trace_pop(void);

#define trace(expr) ({     \
    trace_push(GET_TRACE); \
    expr;                  \
    trace_pop();           \
})

#define trace_ret(expr) ({         \
    trace_push(GET_TRACE);         \
    __typeof__(expr) ret = (expr); \
    trace_pop();                   \
    ret;                           \
})

//
// panic

void panic_impl(TRACE, bool expr, const char* fmt, ...);

#define panic(expr, fmt, ...) panic_impl(GET_TRACE, (expr), (fmt), ##__VA_ARGS__)

#define null_panic(ptr) panic((ptr), "pointer \"%s\" is NULL", #ptr)

#endif