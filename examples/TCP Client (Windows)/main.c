// =====
// Please Read:
// This code uses Winsock 2.2.
// Command:
//   ./run.bat "TCP Client (Windows)" "-lws2_32"
// =====
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(void) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
    WSACleanup();
        return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567); // Target Port
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
        printf("Invalid IP address\n");
        closesocket(sock);
    WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(sock);
    WSACleanup();
        return 1;
    }

    const char *message = "Hello World";
    int offset = 0;
    int length = (int)strlen(message);
    while (offset < length) {
        int sent = send(sock, message + offset, length - offset, 0);
        if (sent <= 0) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(sock);
    WSACleanup();
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
        printf("recv failed: %d\n", WSAGetLastError());
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
