// =====
// Please Read:
// This code is using openssl/sha.h
// You must add option to '-lcrypto'
// 
// Command:
//   Windows - ./run.bat "SHA256 Hash" "-lcrypto"
//   Other - ./run.sh "SHA256 Hash" "-lcrypto"
// =====

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
int main(void) {
    char *string = "Hello World"; // hash string
    unsigned char hash[SHA256_DIGEST_LENGTH]; // hash
    SHA256((unsigned char*)string, strlen(string), hash); // processing sha256 hash

    printf("Result: ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}