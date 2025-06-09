#include <stdio.h>
#include "trace.h"

double divide(int a, int b) {
    panic(b != 0, "divisor should not be 0");
    return (double)a / b;
}

int main() {
    int a = 42;
    int b = 0;
    double result = trace_ret(divide(a, b));

    printf("%lf\n", result);
}