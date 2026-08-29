#include <stdio.h>

int main(void) {
    int a = 1234;
    int *ptr = &a; // read pointer address

    // &variable : Pointer Address
    // *pointer  : Reading Pointer
    printf("a pointer address: %X\n", ptr);
    printf("read result: %d\n", *ptr);
    return 0;
}