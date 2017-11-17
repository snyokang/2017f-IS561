#include <stdio.h>
#include <stdlib.h>

int foo() {puts("foo"); return 0;}
int main() {
    int var;
    printf("%p, %p, %p\n", &var, foo, malloc(4));
    return 0;
}
