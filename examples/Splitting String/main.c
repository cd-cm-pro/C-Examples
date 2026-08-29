#include <stdio.h>
#include <string.h>

int main(void) {
    char str[20] = "apple,banana,orange";
    char splitted[3][20] = {};

    char item[7] = {};

    int i = 0;
    int item_i = 0;
    int spl_i = 0;
    char splitting_char = ',';
    while(str[i] != '\0') {
        char ch = str[i];
        if (ch == splitting_char) {
            item_i = 0;
            strcpy(splitted[spl_i], item);
            spl_i++;
        } else {
            item[item_i] = ch;
            item_i++;
        }
        if (str[i+1] == '\0') {
            strcpy(splitted[spl_i], item);
            break;
        }
        i++;
    }

    for (int i = 0; i < 3; i++) {
        char spl_item[20];
        strcpy(spl_item, splitted[i]);
        printf("%s\n", spl_item);
    }
    return 0;
}