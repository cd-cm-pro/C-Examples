#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    rand();
    int min = 5;
    int max = 10;
    int result = min + ((double)rand() / 32767) * ((max + 1) - min);
    printf("Result: %d\n", result);
    return 0;
}