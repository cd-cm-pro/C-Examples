#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("./files/sample.txt", "r"); // Open the file

    if (f == NULL) { // check file open failed
        printf("Cannot open the file");
        return 1;
    }

    char line[32];
    char result[128];
    while (fgets(line, sizeof(line), f)!=NULL) {
        strcat(result, line);
    }

    fclose(f); // close file

    printf("Result:\n%s\n", result); // print result
    return 0;
}