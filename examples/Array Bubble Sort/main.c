#include <stdio.h>
#include <string.h>

int main(void) {
    int input[5] = {4, 2, 3, 5, 1};
    int len = sizeof(input) / sizeof(input[0]);
    int result[len];
    memcpy(result, input, sizeof(input));

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