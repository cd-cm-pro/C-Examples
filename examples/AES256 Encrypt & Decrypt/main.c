// =====
// Please Read:
// This code is using openssl/aes.h
// You must add option to '-lcrypto'
// 
// Command:
//   Windows - ./run.bat "AES256 Encrypt & Decrypt" "-lcrypto"
//   Other - ./run.sh "AES256 Encrypt & Decrypt" "-lcrypto"
// =====

#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int main(void) {
    AES_KEY aeskey;
    unsigned char key[32]; // 32 byte aes key
    unsigned char message[12] = "Hello World";
    unsigned char encrypted[128] = {0};
    unsigned char decrypted[128] = {0};

    printf("before: %s\n", message);

    int encrypt_set = AES_set_encrypt_key(key, 256, &aeskey); // set encrypt key
    if (encrypt_set < 0) {
        printf("AES Encrypt key set error");
        return 1;
    }
    AES_ecb_encrypt(message, encrypted, &aeskey, AES_ENCRYPT); // encrypt

    printf("encrypted: ");
    for (int i = 0; i < strlen(encrypted); i++) {
        printf("%X", encrypted[i]);
    }
    printf("\n");

    int decrypt_set = AES_set_decrypt_key(key, 256, &aeskey); // set decrypt key
    if (decrypt_set < 0) {
        printf("AES Decrypt key set error");
        return 1;
    }
    AES_ecb_encrypt(encrypted, decrypted, &aeskey, AES_DECRYPT); // decrypt
    printf("decrypted: %s\n", decrypted);

    return 0;
}

#pragma GCC diagnostic pop