// =====
// Please Read:
// This code is using openssl
// You must add option to '-lssl -lcrypto'
//
// Command:
//   ./run.sh "HTTPS TCP Client" "-lssl -lcrypto"
// =====

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(void) {
    int sock;
    struct sockaddr_in addr = {};

    struct hostent *host;
    host = gethostbyname("sha256.badssl.com"); // Only Domain!!!
    if (host == NULL)
    {
        printf("DNS Lookup Failed");
        return 1;
    }

    // Create Socket
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("socket failed\n");
        return 0;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443); // Target Port
    memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);
    
    int connect_result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (connect_result != 0) {
        printf("Connect Failed");
        close(sock);
        return 0;
    }

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx)
    {
        printf("SSL_CTX_new Error:\n");
        ERR_print_errors_fp(stderr);
        close(sock);
        return 1;
    }

    SSL *ssl = SSL_new(ctx);
    if (!ssl)
    {
        printf("SSL_new Error:\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        close(sock);
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
        close(sock);
        return 1;
    }

    char request[4096] = {0};

    // HTTP Header
    strcat(request, "GET / HTTP/1.1\r\n");
    strcat(request, "Host: sha256.badssl.com\r\n");
    strcat(request, "Connection: close\r\n");
    strcat(request, "\r\n");

    // Send Request
    SSL_write(ssl, request, (int)strlen(request));

    char buffer[4096];
    int received;
    while (1)
    {
        int len = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (len <= 0) break;
        buffer[len] = 0;
        printf("Result:\n%s\n", buffer);
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    
    close(sock);
    return 0;
}