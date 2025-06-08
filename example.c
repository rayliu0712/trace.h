#include <stdio.h>
#include "trace.h"

double divide(TRACE, int a, int b) {
    trace();

    panic(b != 0, "divisor should not be 0");
    return (double)a / b;
}

int main() {
    trace_init();

    int a = 42;
    int b = 0;
    double result = divide(GET_TRACE, a, b);
    printf("%lf\n", result);
}