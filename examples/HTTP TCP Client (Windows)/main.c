// =====
// Please Read:
// This code is using winsock2.h
// You must add option to '-lws2_32'
//
// Command:
//   ./run.bat "HTTP TCP Client (Windows)" "-lws2_32"
// =====

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
    WSADATA wsa;
    SOCKET sock;
    SOCKADDR_IN addr;

    // MAKEWORD(2, 2) = Winsock version 2.2
    // Return Values:
    //   Success = 0
    //   Failure = SOCKET_ERROR
    int wsa_startup_result = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (wsa_startup_result != 0)
    {
        printf("WSAStartup Failed");
        return 1;
    }

    // If you need Domain address instead
    // of IP address, You should use
    // gethostbyname (ws2tcpip.h) Function
    // to do Lookup DNS Server.
    // ---------------------------------------
    // struct hostent *host;
    // host = gethostbyname("http.badssl.com");
    // if (host == NULL) {
    //     printf("DNS Lookup Failed");
    //     WSACleanup();
    //     return 1;
    // }

    // Create Socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);                          // Target Port
    addr.sin_addr.s_addr = inet_addr("104.154.89.105"); // Target IP
    // memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);

    int connect_result = connect(sock, (SOCKADDR *)&addr, sizeof(addr));
    if (connect_result != 0)
    {
        printf("Connect Failed");
        closesocket(sock);
        WSACleanup();
        return 1;
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
        printf("Result:\n%s\n", buffer); // Print result
    }

    closesocket(sock); // Close Socket
    WSACleanup();      // Cleanup WSA
    return 0;
}