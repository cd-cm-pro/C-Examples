#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[12] = "Hello World";
    char str2[12] = "Hello World";
    char str3[9] =  "Hi World";

    int compare1 = strcmp(str1, str2);
    if (compare1 == 0) {
        printf("str1 == str2 -> true\n");
    } else {
        printf("str1 == str2 -> false\n");
    }

    int compare2 = strcmp(str1, str3);
    if (compare2 == 0) {
        printf("str1 == str3 -> true");
    } else {
        printf("str1 == str3 -> false");
    }
    return 0;
}