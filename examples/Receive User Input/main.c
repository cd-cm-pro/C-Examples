#include <stdio.h>

int main(void) {
    int a;
    int b;
    
    printf("input 1: ");
    scanf("%d", &a);
    printf("input 2: ");
    scanf("%d", &b);

    printf("\n%d + %d = %d\n", a, b, a + b);
    return 0;
}