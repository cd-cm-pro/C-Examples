// =====
// Please Read:
// This code is using winsock2.h
// You must add option to '-lws2_32'
//
// Command:
//   ./run.bat "HTTP TCP Server (Windows)" "-lws2_32"
// =====

#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
    WSADATA wsa;
    SOCKET sock, sock_cl;
    SOCKADDR_IN addr, addr_cl;
    int addr_cl_len = sizeof(addr_cl);

    int buffer_max_size = 4096;
    char buffer[buffer_max_size];

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

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        printf("socket failed: %d\n", WSAGetLastError());
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Server IP (INADDR_ANY is auto)
    addr.sin_port = htons(8080); // Server Port

    int bind_result = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (bind_result == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    int listen_result = listen(sock, 5); // Queue max 5
    if (listen_result == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    printf("server listen at http://localhost:8080\n");

    while (1) {
        sock_cl = accept(sock, (struct sockaddr*)&addr_cl, &addr_cl_len);
        if (sock_cl == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            continue;
        }
        memset(buffer, 0, sizeof(buffer));

        int received = recv(sock_cl, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = 0;
            printf("request:\n%s\n", buffer);

            char *resp_body = "<title>C Server</title><h1>Hello World</h1>";
            int resp_length = strlen(resp_body);
            char resp[buffer_max_size];
            char *response =
                "HTTP/1.1 200 OK\r\n" // status code
                "Content-Type: text/html; charset=utf-8\r\n" // content type
                "Content-Length: %d\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s";
            sprintf(resp, response, resp_length, resp_body);
            send(sock_cl, resp, (int)strlen(resp), 0); // data send
        }

        closesocket(sock_cl);
    }
    closesocket(sock);
    WSACleanup();

    return 0;
}