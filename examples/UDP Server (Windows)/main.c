// =====
// Please Read:
// This code uses Winsock 2.2.
// Command:
//   ./run.bat "UDP Server (Windows)" "-lws2_32"
// =====
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(void) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
    WSACleanup();
        return 1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567); // Server Port
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // Server IP

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket(sock);
    WSACleanup();
        return 1;
    }

    printf("UDP Server listening on port 4567\n");
    while (1) {
        char buffer[1024];
        struct sockaddr_in from_addr = {0};
        int from_len = sizeof(from_addr);
        int received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr*)&from_addr, &from_len);
        if (received < 0) {
            printf("recvfrom failed: %d\n", WSAGetLastError());
            continue;
        }
        buffer[received] = '\0';
        printf("received: %s\n", buffer);
        const char *response = "Hello from UDP Server";
        if (sendto(sock, response, (int)strlen(response), 0,
                   (struct sockaddr*)&from_addr, from_len) < 0) {
            printf("sendto failed: %d\n", WSAGetLastError());
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
