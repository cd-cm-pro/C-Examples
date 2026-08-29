#include <stdio.h>

int main(void) {
    int arr[5] = {4, 2, 6, 8, 3}; // Create Array
    int size = sizeof(arr) / sizeof(arr[0]); // get array size
    for (int i = 0; i < size; i++) {
        int item = arr[i]; // get item from index
        if (i == size-1) { // branch last index
            printf("%d\n", item); // print number
            break;
        }
        printf("%d, ", item); // print number
    }
    return 0;
}