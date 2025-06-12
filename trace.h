#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

//
/*    impl    */

#define TRACE_ARGS const char *file, const char *func, int line

void trace_impl_push(TRACE_ARGS);

void trace_impl_pop(void);

void panic_impl(TRACE_ARGS, bool expr, const char* fmt, ...);

#undef TRACE_ARGS

//
/*    api    */

#define GET_TRACE __FILE__, __func__, __LINE__

#define TRACE(expr)                 \
    do {                            \
        trace_impl_push(GET_TRACE); \
        (expr);                     \
        trace_impl_pop();           \
    } while (0)

#define PANIC(expr, msg) panic_impl(GET_TRACE, (expr), (msg));

#define PANIC_F(expr, fmt, ...) panic_impl(GET_TRACE, (expr), (fmt), __VA_ARGS__)

#define PANIC_NULL(ptr) PANIC_F((ptr), "pointer \"%s\" is NULL", #ptr)

#endif
