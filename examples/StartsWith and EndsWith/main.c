#include <stdio.h>
#include <string.h>

int starts_with(char input[], char s[]) {
    int input_len = strlen(input);
    int s_len = strlen(s);

    if (input_len < s_len) return 0;
    for (int i = 0; i < s_len; i++) {
        char ch = input[i];
        char s_ch = s[i];
        if (ch != s_ch) return 0;
    }
    return 1;
}
int ends_with(char input[], char s[]) {
    int input_len = strlen(input);
    int s_len = strlen(s);

    if (input_len < s_len) return 0;
    int j = 0;
    for (int i = input_len - s_len; i < input_len; i++) {
        char ch = input[i];
        char s_ch = s[j];
        if (ch != s_ch) return 0;
        j++;
    }
    return 1;
}

int main(void) {
    char input[12] = "Hello World";
    printf("Input: %s\n", input);

    printf("starts with 'Hello': %s\n", starts_with(input, "Hello") ? "Yes" : "No");
    printf("starts with 'asdf': %s\n", starts_with(input, "asdf") ? "Yes" : "No");
    printf("starts with 'qwert': %s\n", starts_with(input, "qwert") ? "Yes" : "No");
    printf("starts with 'Hel': %s\n", starts_with(input, "Hel") ? "Yes" : "No");
    printf("starts with 'Helaa': %s\n", starts_with(input, "Helaa") ? "Yes" : "No");

    printf("ends with 'World': %s\n", ends_with(input, "World") ? "Yes" : "No");
    printf("ends with 'asdf': %s\n", ends_with(input, "asdf") ? "Yes" : "No");
    printf("ends with 'qwert': %s\n", ends_with(input, "qwert") ? "Yes" : "No");
    printf("ends with 'rld': %s\n", ends_with(input, "rld") ? "Yes" : "No");
    printf("ends with 'aarld': %s\n", ends_with(input, "aarld") ? "Yes" : "No");
    return 0;
}