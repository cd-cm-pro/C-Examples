#include <stdio.h>

int main(void) {
    int start = 1;
    int loop = 20;
    for (int i = start; i <= loop; i++) {
        printf("%d: %s\n", i, (i % 2 == 0) ? "even" : "odd");
    }
    return 0;
}