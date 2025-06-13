#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

//
/*   api   */

#define TRACE __FILE__, __func__, __LINE__

#define TRACE_ARGS const char *trace_file, const char *trace_func, int trace_line

#define TRACE_IT char trace_it __attribute__((cleanup(trace_impl_pop))) = trace_impl_push(trace_file, trace_func, trace_line)

#define PANIC(expr, fmt, ...) panic_impl(TRACE, (expr), (fmt), ##__VA_ARGS__)

#define PANIC_NULL(ptr) panic_impl(TRACE, (ptr), "pointer \"%s\" is NULL", #ptr)

//
/*   impl   */

char trace_impl_push(TRACE_ARGS);

void trace_impl_pop(void* ptr);

void panic_impl(TRACE_ARGS, bool expr, const char* fmt, ...);

#endif
