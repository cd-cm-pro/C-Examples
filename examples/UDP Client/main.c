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
    addr.sin_port = htons(4567); // Target Port
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
        printf("Invalid IP address\n");
        close(sock);
        return 1;
    }


    // Send Message
    const char *message = "Hello World";
    if (sendto(sock, message, (int)strlen(message), 0,
               (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("sendto failed: %d\n", errno);
        close(sock);
        return 1;
    }
    char buffer[1024];
    struct sockaddr_in from_addr = {0};
    socklen_t from_len = sizeof(from_addr);
    int received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                            (struct sockaddr*)&from_addr, &from_len);
    if (received >= 0) {
        buffer[received] = '\0';
        printf("received: %s\n", buffer);
    } else {
        printf("recvfrom failed: %d\n", errno);
    }

    close(sock);
    return 0;
}
