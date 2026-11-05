#include "server.h"
#include "log.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void signal_handler(int sig)
{
    (void)sig;
    running = 0;
}

int main() {
    printf("--- Webserver wird gestartet ---\n");
    DEBUG_LOG("Starting server...");

    // Register handler — replaces signal(SIGINT, signal_handler)
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigaction(SIGINT, &sa, NULL);

    // create and let socket listen.
    int net_socket = run_socket();
    if (0 != net_socket) {
        return -1;
    }
    return 0;
}