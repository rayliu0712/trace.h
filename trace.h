#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

#define TRACE_ARGS const char *file, const char *func, int line

#define GET_TRACE __FILE__, __func__, __LINE__

//
// trace

void trace_impl_push(TRACE_ARGS);

void trace_impl_pop(void);

#define TRACE(expr) ({          \
    trace_impl_push(GET_TRACE); \
    expr;                       \
    trace_impl_pop();           \
})

#define TRACE_R(expr) ({         \
    trace_impl_push(GET_TRACE);  \
    __typeof__(expr) r = (expr); \
    trace_impl_pop();            \
    r;                           \
})

//
// panic

void panic_impl(TRACE_ARGS, bool expr, const char* fmt, ...);

#define PANIC(expr, fmt, ...) panic_impl(GET_TRACE, (expr), (fmt), ##__VA_ARGS__)

#define PANIC_NULL(ptr) PANIC((ptr), "pointer \"%s\" is NULL", #ptr)

#undef TRACE_ARGS

#endif
