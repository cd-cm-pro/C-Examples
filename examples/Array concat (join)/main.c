#include <stdio.h>
#include <string.h>

int main(void) {
    char arr[][10] = { // input
        "Apple",
        "Banana",
        "Orange"
    };
    int item_size = sizeof(arr) / sizeof(arr[0]);
    int content_size = sizeof(arr[0]) / sizeof(arr[0][0]);
    char separator[2] = " ";
    char result[item_size * content_size];

    for (int i = 0; i < item_size; i++) {
        char item[content_size];
        strcpy(item, arr[i]);
        strcat(result, item);
        if (i < item_size - 1) {
            strcat(result, separator);
        }
    }

    printf("Result: %s", result);
    return 0;
}