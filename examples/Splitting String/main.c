#include <stdio.h>
#include <string.h>

int main(void) {
    char str[20] = "apple,banana,orange";
    char splitted[3][7] = {};

    char item[7] = {};

    int i = 0;
    int item_i = 0;
    int spl_i = 0;
    char splitting_char = ',';
    while(str[i] != '\0') {
        if (str[i] == splitting_char) {
            splitted[spl_i][item_i] = '\0';
            spl_i++;
            item_i = 0;
        } else {
            splitted[spl_i][item_i] = str[i];
            item_i++;
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