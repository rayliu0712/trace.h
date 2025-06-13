# trace.h

## Example

```c
#include <stdio.h>
#include "trace.h"

double divide(TRACE_ARGS, int a, int b) {
    TRACE_IT;
    PANIC(b != 0, "divisor should not be 0");

    return (double)a / b;
}

void print_addr_if_not_null(TRACE_ARGS, void* ptr) {
    TRACE_IT;
    PANIC_NULL(ptr);

    printf("%p\n", ptr);
}

int main(void) {
    // comment or uncomment below lines to see example
    
    double r = divide(TRACE, 42, 0);
    printf("%f\n", r);

    print_addr_if_not_null(TRACE, NULL);
}
```