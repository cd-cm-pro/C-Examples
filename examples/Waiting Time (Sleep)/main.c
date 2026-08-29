#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void wait(int t) {
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(t);
    #else
        sleep((float)t / 1000);
    #endif
}

int main(void) {
    printf("Wait 3 Times...\n");
    wait(3000);
    printf("You did Waited 3 Times.\n");
}