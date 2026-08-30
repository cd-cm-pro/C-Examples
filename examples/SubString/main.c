#include <stdio.h>
#include <string.h>

int main(void) {
    char input[12] = "Hello World";
    char substring[12];
    int len = strlen(input);
    int start = 2;
    int end = 6;
    int j = 0;
    for (int i = start; i <= end; i++) {
        substring[j] = input[i];
        j++;
    }
    substring[end+1] = '\0';
    printf("Input: %s\n", input);
    printf("Substring: %s\n", substring);
    return 0;
}