#include <stdio.h>
#include <windows.h>

int main(void) {
    MessageBoxA(NULL, "Hello World", "Title", 0);

    MessageBoxA(NULL, "Error Icon", "Example 1", MB_ICONERROR);
    MessageBoxA(NULL, "Warning Icon", "Example 2", MB_ICONWARNING);
    MessageBoxA(NULL, "Information Icon", "Example 3", MB_ICONINFORMATION);
    MessageBoxA(NULL, "Question Icon", "Example 4", MB_ICONQUESTION);

    int r1 = MessageBoxA(NULL, "OKCANCEL", "Example 5", MB_OKCANCEL);
    printf("r1: %d\n", r1);

    int r2 = MessageBoxA(NULL, "RETRYCANCEL", "Example 6", MB_RETRYCANCEL);
    printf("r2: %d\n", r2);

    int r3 = MessageBoxA(NULL, "YESNO", "Example 7", MB_YESNO);
    printf("r3: %d\n", r3);

    int r4 = MessageBoxA(NULL, "YESNOCANCEL", "Example 8", MB_YESNOCANCEL);
    printf("r4: %d\n", r4);

    int r5 = MessageBoxA(NULL, "HELP", "Example 9", MB_HELP);
    printf("r5: %d\n", r5);

    int r6 = MessageBoxA(NULL, "ABORTRETRYIGNORE", "Example 10", MB_ABORTRETRYIGNORE);
    printf("r6: %d\n", r6);

    int r7 = MessageBoxA(NULL, "CANCELTRYCONTINUE", "Example 11", MB_CANCELTRYCONTINUE);
    printf("r7: %d\n", r7);

    MessageBoxA(NULL, "MB_TOPMOST", "Example 12", MB_TOPMOST);
    return 0;
}