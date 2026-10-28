#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Server IP
    addr.sin_port = htons(8080); // Server Port
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0 || listen(sock, 5) != 0) {
        perror("bind/listen failed");
        close(sock);
        return 1;
    }
    printf("server listen at http://localhost:8080\n");
    while (1) {
        int client = accept(sock, NULL, NULL);
        if (client < 0) {
            perror("accept failed");
            continue;
        }
        char buffer[4096];
        int received = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            printf("request:\n%s\n", buffer);
            const char *body = "<title>C Server</title><h1>Hello World</h1>";
            char response[4096];
            int length = snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n"
                "Content-Length: %zu\r\nConnection: close\r\n\r\n%s", strlen(body), body);
            if (length > 0 && length < (int)sizeof(response)) {
                int offset = 0;
                while (offset < length) {
                    int sent = send(client, response + offset, length - offset, 0);
                    if (sent <= 0) break;
                    offset += sent;
                }
            }
        }
        close(client);
    }
    close(sock);
    return 0;
}
