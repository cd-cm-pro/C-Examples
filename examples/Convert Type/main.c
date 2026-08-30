#include <stdio.h>

int main(void) {
    printf("(int)5.2f = %d\n", (int)5.2f);
    printf("(int)9.5f = %d\n", (int)9.5f);
    printf("(float)5 = %f\n", (float)5);

    double d = 1.234567890123;
    printf("(float)1.234567890123 double = %f\n", (float)d);
    return 0;
}