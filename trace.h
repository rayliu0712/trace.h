#ifndef TRACE_H
#define TRACE_H

#include <stdbool.h>

#define TRACE const char *trace_file, const char *trace_func, int trace_line

#define GET_TRACE __FILE__, __func__, __LINE__

//
// trace_init

void* trace_init_impl(void);

void trace_free(void**);

#define trace_init() void* trace_auto __attribute__((cleanup(trace_free))) = trace_init_impl()

//
// trace

void* trace_impl(TRACE);

void untrace(void**);

#define trace() void* trace_auto __attribute__((cleanup(untrace))) = trace_impl(trace_file, trace_func, trace_line)

//
// panic

void panic_impl(TRACE, bool expr, const char* fmt, ...);

#define panic(expr, fmt, ...) panic_impl(GET_TRACE, (expr), (fmt), ##__VA_ARGS__)

#define nulpanic(ptr) panic(!(ptr), "pointer \"%s\" is NULL", #ptr)

#endif