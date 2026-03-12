/*
    Author: Gabriel Hernandez
    CPAN226 Lab 4 - Multithreading and Network Concurrency
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define sleep(x) Sleep(1000 * (x))
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#define PORT 8080

typedef struct {
    SOCKET client_socket;
    int client_id;
} client_data;

void handle_client(SOCKET client_socket, int client_id) {
    char *message =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello Client!";

    printf("[Thread %d] Handling client %d...\n", client_id, client_id);
    printf("[Thread %d] Processing request for 5 seconds...\n", client_id);

    sleep(5);

    send(client_socket, message, (int)strlen(message), 0);
    printf("[Thread %d] Response sent to client %d. Closing connection.\n", client_id, client_id);

#ifdef _WIN32
    closesocket(client_socket);
#else
    close(client_socket);
#endif
}