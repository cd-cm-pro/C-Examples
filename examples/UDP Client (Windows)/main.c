// =====
// Please Read:
// This code is using winsock2.h
// You must add option to '-lws2_32'
// 
// Command:
//   ./run.bat "UDP Client (Windows)" "-lws2_32"
// =====

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

int main(void) {
    WSADATA wsa;
    SOCKET sock;
    SOCKADDR_IN addr;

    // MAKEWORD(2, 2) = Winsock version 2.2
    // Return Values:
    //   Success = 0
    //   Failure = SOCKET_ERROR
    int wsa_startup_result = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (wsa_startup_result != 0) {
        printf("WSAStartup Failed");
        return 0;
    }

    // If you need Domain address instead
    // of IP address, You should use
    // gethostbyname (ws2tcpip.h) Function
    // to do Lookup DNS Server.
    // ---------------------------------------
    // struct hostent *host;
    // host = gethostbyname("domain name");
    // if (host == NULL) {
    //     printf("DNS Lookup Failed");
    //     WSACleanup();
    //     return 1;
    // }

    // Create Socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567); // Target Port
    // memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);

    int inet_pton_result = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // Target IP
    if (inet_pton_result != 1) {
        printf("invaild ip address\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    int connect_result = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
    if (connect_result != 0) {
        printf("Connect Failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    const char *message = "Hello World";
    int send_res = sendto(sock, message, (int)strlen(message), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (send_res == SOCKET_ERROR) {
        printf("sendto failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    char buffer[1024];

    SOCKADDR_IN from_addr;
    int from_len = sizeof(from_addr);
    int received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&from_addr, &from_len);

    if (received != SOCKET_ERROR) {
        buffer[received] = '\0';
        printf("received: %s\n", buffer);
    } else {
        printf("error");
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}