#include <stdio.h>

int main(void) {
    printf("!%d = %d (NOT)\n", 1, !1);
    printf("%d & %d = %d (AND)\n", 2, 3, 2 & 3);
    printf("%d | %d = %d (OR)\n", 4, 5, 4 & 5);
    printf("%d ^ %d = %d (XOR)\n", 6, 7, 6 & 7);
    return 0;
}