#include <stdio.h>
#include <string.h>

int main(void) {
    char input[15] = "    He ll  o  "; // input
    int len = strlen(input);
    // left trim
    char ltrim[15] = {0};
    for (int i = 0; i < len; i++) {
        char ch = input[i];
        if (ch == ' ') continue;
        int k = 0;
        for (int j = i; j <= len; j++) {
            ltrim[k] = input[j];
            k++;
        }
        ltrim[k] = 0;
        break;
    }

    // right trim
    char rtrim[15] = {0};
    for (int i = len - 1; i >= 0 && i < len; i--) {
        char ch = input[i];
        if (ch == ' ') continue;
        int j;
        for (j = 0; j <= i; j++) {
            rtrim[j] = input[j];
        }
        rtrim[j] = 0;
        break;
    }

    // print messages
    printf("Input: \"%s\"\n", input);
    printf("Left Trim: \"%s\"\n", ltrim);
    printf("Right Trim: \"%s\"\n", rtrim);

    return 0;
}