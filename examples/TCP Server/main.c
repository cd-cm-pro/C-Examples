#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("socket failed: %d\n", errno);
        return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567); // Server Port
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Server IP

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("bind failed: %d\n", errno);
        close(sock);
        return 1;
    }

    if (listen(sock, 5) != 0) {
        printf("listen failed: %d\n", errno);
        close(sock);
        return 1;
    }
    printf("TCP Server listening on port 4567\n");
    while (1) {
        int client = accept(sock, NULL, NULL);
        if (client == -1) {
            printf("accept failed: %d\n", errno);
            continue;
        }
        char buffer[1024];
        int received = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            printf("received: %s\n", buffer);
            const char *response = "Hello from TCP Server";
            int offset = 0;
            int length = (int)strlen(response);
            while (offset < length) {
                int sent = send(client, response + offset, length - offset, 0);
                if (sent <= 0) break;
                offset += sent;
            }
        }
        close(client);
    }

    close(sock);
    return 0;
}
