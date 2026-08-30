#include <stdio.h>

int main(void) {
    int size = 10;
    int input[size];
    input[0] = 1;
    input[1] = 5;
    input[2] = 0;
    input[3] = 4;
    input[4] = 7;
    input[5] = 6;
    input[6] = 9;
    input[7] = 1;
    input[8] = 5;
    input[9] = 6;
    
    int result[size];
    int j = 0;
    for (int i = 0; i < size; i++) {
        int v = input[i];
        int test = v >= 5; // test expression
        if (test) result[j++] = v;
    }

    printf("Input: {");
    for (int i = 0; i < size; i++) {
        int item = input[i];
        if (i == size - 1) printf("%d", item);
        else printf("%d, ", item);
    }
    
    printf("}\nResult: {");
    for (int i = 0; i < j; i++) {
        int item = result[i];
        if (i == j - 1) printf("%d", item);
        else printf("%d, ", item);
    }
    printf("}\n");

    return 0;
}