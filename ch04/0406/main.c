#include <stdio.h>
#include "sub.h"

int main() {
    printf("Hello, World!\n");

    int a = 10;
    int b = 3;
    int c = add(a, b);
    printf("add(%d, %d) = %d\n", a, b, c);

    int d = mul(a, b);
    printf("mul(%d, %d) = %d\n", a, b, d);


    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int e = average(array, size);
    printf("average(..., %d) = %d\n", size, e);




    return 0;
}