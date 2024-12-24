#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void close_all(int sock, int status)
{
    shutdown(sock, SHUT_RDWR);
    close(sock);
    exit(status);
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
        exit(1);

    uint16_t port = 0;
    if (sscanf(argv[2], "%hd", &port) == EOF)
        exit(1);

    struct sockaddr_in addr = {.sin_family = AF_INET, .sin_port = htons(port)};
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) == 0)
        exit(1);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        exit(1);

    if (connect(sock, &addr, sizeof(addr)) == -1)
    {
        close(sock);
        exit(1);
    }

    int value;
    while (EOF != scanf("%d", &value))
    {
        int status = send(sock, &value, 4, 0);
        if (status == -1)
            close_all(sock, 1);
        if (status == 0)
            close_all(sock, 0);

        status = recv(sock, &value, 4, 0);
        if (status == -1)
            close_all(sock, 1);
        if (status == 0)
            close_all(sock, 0);
        printf("%d ", value);
    }

    close_all(sock, 0);
}