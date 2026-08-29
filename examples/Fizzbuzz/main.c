#include <stdio.h>

int main(void) {
    int loop = 100; // loop count
    for (int i = 1; i <= loop; i++) {
        if (i%3 == 0 && i%5 == 0) { // 3 Multiple and 5 Multiple
            printf("FizzBuzz\n");
        } else if (i%3 == 0) { // 3 Multiple
            printf("Fizz\n");
        } else if (i%5 == 0) { // 5 Multiple
            printf("Buzz\n");
        } else {
            printf("%d\n", i); // print number
        }
    }

    return 0;
}