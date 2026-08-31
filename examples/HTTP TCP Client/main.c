#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int sock;
    struct sockaddr_in addr = {};

    // Create Socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("socket failed\n");
        return 0;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);                          // Target Port
    addr.sin_addr.s_addr = inet_addr("104.154.89.105"); // Target IP
    
    int connect_result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (connect_result != 0) {
        printf("Connect Failed");
        close(sock);
        return 0;
    }

    char request[4096] = {0};

    // HTTP Header
    strcat(request, "GET / HTTP/1.1\r\n");
    strcat(request, "Host: http.badssl.com\r\n");
    strcat(request, "Connection: close\r\n");
    strcat(request, "\r\n");

    // Send Request
    send(sock, request, (int)strlen(request), 0);

    char buffer[4096];
    int received;
    while ((received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[received] = 0;
        printf("Result:\n%s\n", buffer);
    }
    
    close(sock);
    return 0;
}