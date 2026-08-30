// =====
// Please Read:
// This code is using winsock2.h
// You must add option to '-lws2_32'
// 
// Command:
//   ./run.bat "DNS Check (Windows)" "-lws2_32"
// =====

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main(void) {
    WSADATA wsa;
    struct hostent *host;

    // MAKEWORD(2, 2) = Winsock version 2.2
    // Return Values:
    //   Success = 0
    //   Failure = SOCKET_ERROR
    int wsa_startup_result = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (wsa_startup_result != 0) {
        printf("WSAStartup Failed");
        return 0;
    }

    host = gethostbyname("badssl.com");
    for (int i = 0; host->h_addr_list[i] != NULL; i++) {
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[i], sizeof(addr));

        printf("ip %d: %s\n", i, inet_ntoa(addr));
    }

    WSACleanup(); // Cleanup WSA
    return 0;
}