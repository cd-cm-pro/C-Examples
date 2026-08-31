#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) continue;
        i++;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

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

    quickSort(result, 0, len - 1);
    
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