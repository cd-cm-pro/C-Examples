// =====
// Please Read:
// This code is using zilb.h
// You must add option to '-lz'
// 
// Command:
//   ./run.bat "Zlib Compress, Uncompress" "-lz"
// =====

#include <stdio.h>
#include <string.h>
#include <zlib.h>

int main(void) {
    char input[47] = "HiHiHiHiHiHiHiHiHiHiaaaaaaaaaaaaaaaaaaaaaaaaaa";
    uLong size = strlen(input) + 1;
    uLong compressed_size = compressBound(size);
    uLong decompressed_size = size;
    char deflate_data[compressed_size];
    char inflate_data[compressed_size];
    
    printf("Original: %s\n", input);
    compress(deflate_data, &compressed_size, input, size);

    int len = strlen(deflate_data);
    printf("Compressed: ");
    for (int i = 0; i < len; i++) {
        unsigned char ch = deflate_data[i];
        if (i == len-1) {
            printf("%d", ch);
            break;
        }
        printf("%d,", ch);
    }
    printf("\n");
    uncompress(inflate_data, &decompressed_size, deflate_data, decompressed_size);

    printf("decompressed: %s\n", inflate_data);
    return 0;
}