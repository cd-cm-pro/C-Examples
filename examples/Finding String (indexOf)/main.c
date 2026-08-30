#include <stdio.h>
#include <string.h>

int main(void) {
    char input[12] = "Hello World";
    char find[12] = "llo";
    int i_len = strlen(input);
    int f_len = strlen(find);
    int index = -1;

    for (int i = 0; i < i_len; i++) {
        int equal = 1;
        for (int j = 0; j < f_len; j++) {
            if (input[i + j] != find[j]) {
                equal = 0;
                break;
            }
        }
        if (equal) {
            index = i;
            break;
        }
    }

    printf("Input: %s\n", input);
    printf("Find: %s\n", find);
    printf("result: %d\n", index);
    return 0;
}