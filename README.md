# trace.h

## Example

```c
#include <stdio.h>
#include "trace.h"

double divide(int a, int b) {
    PANIC(b != 0, "divisor should not be 0");

    return (double)a / b;
}

void print_if_not_null(void* ptr) {
    PANIC_NULL(ptr);

    printf("%p\n", ptr);
}

int main(void) {
    // comment or uncomment below lines to see example

    double r;
    TRACE(r = divide(1, 0));
    printf("%f\n", r);

    int* arr = NULL;
    TRACE(print_if_not_null(arr));
}
```