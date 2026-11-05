#include "server.h"
#include "log.h"
#include "file.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

volatile sig_atomic_t running = 1;

static int _create_socket()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > server_fd) {
        perror("Error while trying to create a socket.");

        return -1;
    }

    DEBUG_LOG("Socket created. File descriptor: %d. Start configuring port reusage.", server_fd);

    //port reusage
    int opt = 1;
    if (0 > setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error occurred while trying to setup Port Reuse. setsockopt(SO_REUSEADDR) failed.");
        close(server_fd);

        return -1;
    }

    DEBUG_LOG("Port reusage has been configured successfully.");

    return server_fd;
}

int run_socket()
{
    int server_fd = _create_socket();
    if (0 > server_fd) {
        return -1;
    }

    //fill structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_port = htons(PORT);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind
    if (0 > bind(server_fd, (struct sockaddr*)&servAddr, sizeof(servAddr))) {
        perror("Error while trying to bind socket.");
        close(server_fd);

        return -1;
    }
    printf("Socket was bound to port %d successfully.\n", PORT);

    //listen
    if (0 > listen(server_fd, MAX_CONNECTIONS)) {
        perror("Error occurred while trying to listen with socket.");
        close(server_fd);

        return -1;
    }
    DEBUG_LOG("Listening on %d", PORT);
    printf("Server now listens on port %d!\n", PORT);

    while ( running ) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        printf("Waiting for connections...\n");
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if ( 0 > client_fd ) {
            if (!running) break; // SIGINT case

            perror("Accept failed with client... Continuing with next.");
            continue;
        }

        DEBUG_LOG("Received connection!");

        char *html_doc = read_html_file("www/index.html");
        if (NULL != html_doc) {
            size_t response_size = strlen(html_doc) + 256;
            char *http_response = malloc(response_size);

            snprintf(
                http_response,
                response_size,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: %zu\r\n"
                "\r\n"
                "%s",
                strlen(html_doc),
                html_doc
            );
            send(client_fd, http_response, strlen(http_response), 0);

            free(html_doc);
        } else {
            char *error_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found";

            send(client_fd, error_response, strlen(error_response), 0);
        }

        close(client_fd);
    }

    close(server_fd);
    printf("Server will be shut down accordingly.");

    return 0;
}
