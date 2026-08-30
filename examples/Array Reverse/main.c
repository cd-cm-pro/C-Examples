#include <stdio.h>

int main(void) {
    int arr[5]; // input
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    int result[arr_size];
    for (int i = 0; i < arr_size; i++) {
        int j = arr_size - 1 - i;
        result[i] = arr[j];
    }

    printf("Input: {");
    for (int i = 0; i < arr_size; i++) {
        int item = arr[i];
        if (i >= arr_size - 1) printf("%d", item);
        else printf("%d, ", item);
    }

    printf("}\nResult: {");
    for (int i = 0; i < arr_size; i++) {
        int item = result[i];
        if (i >= arr_size - 1) printf("%d", item);
        else printf("%d, ", item);
    }
    printf("}\n");

    return 0;
}