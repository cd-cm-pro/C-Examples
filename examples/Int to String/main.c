#include <stdio.h>
#include <string.h>

int main(void) {
    int input = 12345;
    char result[6];

    sprintf(result, "%d", input);

    printf("Result: %s\n", result);
    return 0;
}