#include <stdio.h>
#include <conio.h>

int main(void) {
    printf("(q = Exit)\n");

    while (1) {
        char ch = _getch();
        printf("Input Receive: %c\n", ch);
        if (ch == 'q') break;
    }

    return 0;
}