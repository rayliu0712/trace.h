# trace.h

## Example

```c
#include <stdio.h>
#include "trace.h"

double divide(int a, int b) {
    panic(b != 0, "divisor should not be 0");

    return (double)a / b;
}

void index_and_print(int* arr, size_t index) {
    null_panic(arr);

    printf("%d\n", arr[index]);
}

int main(void) {
    // comment or uncomment below lines to see example

    int a = 42;
    int b = 0;
    double result = trace_ret(divide(a, b));
    printf("%f\n", result);

    int* arr = NULL;
    trace(index_and_print(arr, 5));
}
```