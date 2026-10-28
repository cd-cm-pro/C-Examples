#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int main(void) {
    // Create Socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("socket failed: %d\n", errno);
        return 1;
    }

    // Configure IPv4 address
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567); // Server Port
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Server IP

    // Bind Socket
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("bind failed: %d\n", errno);
        close(sock);
        return 1;
    }

    printf("UDP Server listening on port 4567\n");
    while (1) {
        char buffer[1024];
        struct sockaddr_in from_addr = {0};
        socklen_t from_len = sizeof(from_addr);
        int received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr*)&from_addr, &from_len);
        if (received < 0) {
            printf("recvfrom failed: %d\n", errno);
            continue;
        }
        buffer[received] = '\0';
        printf("received: %s\n", buffer);
        const char *response = "Hello from UDP Server";
        if (sendto(sock, response, (int)strlen(response), 0,
                   (struct sockaddr*)&from_addr, from_len) < 0) {
            printf("sendto failed: %d\n", errno);
        }
    }

    close(sock);
    return 0;
}
