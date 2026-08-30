// =====
// Please Read:
// This code is using winsock2.h and openssl
// You must add option to '-lws2_32 -lssl -lcrypto'
//
// Command:
//   ./run.bat "HTTPS TCP Client (Windows)" "-lws2_32 -lssl -lcrypto"
// =====

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
        return 0;
    }

    struct hostent *host;
    host = gethostbyname("sha256.badssl.com"); // Only Domain!!!
    if (host == NULL)
    {
        printf("DNS Lookup Failed");
        WSACleanup();
        return 1;
    }

    // Create Socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(443); // Target Port
    memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);

    int connect_result = connect(sock, (SOCKADDR *)&addr, sizeof(addr));
    if (connect_result != 0)
    {
        printf("Connect Failed");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // ssl start
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx)
    {
        printf("SSL_CTX_new Error:\n");
        ERR_print_errors_fp(stderr);
        closesocket(sock); // close socket
        return 1;
    }

    SSL *ssl = SSL_new(ctx);
    if (!ssl)
    {
        printf("SSL_new Error:\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        closesocket(sock); // close socket
        return 1;
    }

    SSL_set_tlsext_host_name(ssl, "sha256.badssl.com"); // Only Domain!!!
    SSL_set_fd(ssl, (int)sock);

    int ssl_conn = SSL_connect(ssl);
    if (ssl_conn <= 0)
    {
        printf("TLS handshake failed:\n");
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        closesocket(sock); // close socket
        return 1;
    }

    char request[4096] = {0};

    // HTTP Header
    strcat(request, "GET / HTTP/1.1\r\n");
    strcat(request, "Host: sha256.badssl.com\r\n");
    strcat(request, "Connection: close\r\n");
    strcat(request, "\r\n");

    // Send Request
    // send(sock, request, (int)strlen(request), 0); // old code
    SSL_write(ssl, request, (int)strlen(request));

    char buffer[4096];
    int received;
    // old code
    // while((received = recv(sock, buffer, sizeof(buffer) - 1, 0))>0) {
    //     buffer[received]=0;
    //     printf("Result:\n%s", buffer); // Print result
    // }
    while (1)
    {
        int len = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (len <= 0)
            break;

        buffer[len] = 0;
        printf("Result:\n%s", buffer);
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    closesocket(sock); // Close Socket
    WSACleanup();      // Cleanup WSA
    return 0;
}