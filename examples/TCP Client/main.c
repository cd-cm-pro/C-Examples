#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int main(void) {
    // Create Socket
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

    // Connect to Server
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("connect failed: %d\n", errno);
        close(sock);
        return 1;
    }

    // Send Message
    const char *message = "Hello World";
    int offset = 0;
    int length = (int)strlen(message);
    while (offset < length) {
        int sent = send(sock, message + offset, length - offset, 0);
        if (sent <= 0) {
            printf("send failed: %d\n", errno);
            close(sock);
            return 1;
        }
        offset += sent;
    }
    char buffer[1024];
    int received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("received: %s\n", buffer);
    } else if (received < 0) {
        printf("recv failed: %d\n", errno);
    }

    close(sock);
    return 0;
}
