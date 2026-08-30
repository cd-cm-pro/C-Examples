#include <stdio.h>
#include <string.h>

int main(void) {
    char input[12] = "Hello World"; // input
    char upper[12];
    char lower[12];

    strcpy(upper, input);
    strcpy(lower, input);

    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        char ch = upper[i];
        if (ch >= 'a' && ch <= 'z') {
            upper[i] = ch - 32;
        }
    }

    for (int i = 0; i < len; i++) {
        char ch = lower[i];
        if (ch >= 'A' && ch <= 'Z') {
            lower[i] = ch + 32;
        }
    }

    // print messages
    printf("Input: %s\n", input);
    printf("Upper: %s\n", upper);
    printf("Lower: %s\n", lower);
    return 0;
}