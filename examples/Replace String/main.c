#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[12] = "Hello World";
    char replaced1[50] = "";
    printf("Original: %s\n", str1);
    for (int i = 0; i < strlen(str1); i++) {
        char ch = str1[i];
        if (ch == 'o') {
            strcat(replaced1, "e"); // o -> e
            continue;
        } else if (ch == 'l') {
            strcat(replaced1, "ab"); // l -> ab
            continue;
        }
        char ch_[2] = {ch, 0};
        strcat(replaced1, ch_);
    }
    printf("Replaced: %s\n\n", replaced1);

    char str2[44] = "Apple Apple Banana Orange Orange Watermelon";
    char replaced2[50] = "";
    printf("Original: %s\n", str2);
    int i = 0;
    while (str2[i] != '\0') {
        if (str2[i] == 'O' && 
            str2[i+1] == 'r' && 
            str2[i+2] == 'a' && 
            str2[i+3] == 'n' && 
            str2[i+4] == 'g' && 
            str2[i+5] == 'e')
        {
            strcat(replaced2, "Strawberry"); // Orange -> Strawberry
            i += 6;
            continue;
        }
        char ch_[2] = {str2[i], 0};
        strcat(replaced2, ch_);
        i++;
    }
    printf("Replaced: %s\n", replaced2);
    return 0;
}