#include <stdio.h>

int main(void) {
    int len = 5;
    int input[len];
    input[0] = 4;
    input[1] = 2;
    input[2] = 3;
    input[3] = 5;
    input[4] = 1;

    int result[len];
    for (int i = 0; i < 5; i++) {
        result[i] = input[i];
    }

    int temp;
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (result[j] > result[j + 1]) {
                temp = result[j];
                result[j] = result[j+1];
                result[j+1] = temp;
            }
        }
    }
    
    printf("Input: {");
    for (int i = 0; i < len; i++) {
        int item = input[i];
        if (i == len - 1) printf("%d", item);
        else printf("%d, ", item);
    }
    printf("}\nResult: {");
    for (int i = 0; i < len; i++) {
        int item = result[i];
        if (i == len - 1) printf("%d", item);
        else printf("%d, ", item);
    }
    printf("}\n");
    return 0;
}