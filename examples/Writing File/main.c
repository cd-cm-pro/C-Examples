#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("./files/wrote.txt", "w"); // Open the file

    if (f == NULL) { // check file open failed
        printf("Cannot open the file");
        return 1;
    }

    char write_content[12] = "Hello World";
    fwrite(write_content, 1, strlen(write_content), f);

    fclose(f);
    return 0;
}