#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_address_length;
    srand(time(NULL));

    // Create a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket== -1) {
        perror("Could not create socket");
        exit(1);
    }

    // Set up the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(serverSocket);
        exit(1);
    }

    // Listen for incoming connections
    listen(serverSocket, 5);
    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        client_address_length = sizeof(client_addr);

        // Accept a new client connection
        clientSocket = accept(serverSocket, (struct sockaddr *)&client_addr, &client_address_length);
        if (clientSocket < 0) {
            perror("Error accepting connection");
            close(serverSocket);
            exit(1);
        }

        // Generate a random number between 100 and 999
        int randomNumber = rand() % 900 + 100;

        // Send the random number to the client
        send(clientSocket, &randomNumber, sizeof(randomNumber), 0);
        printf("Sent random to the client: %d\n", randomNumber);

        close(clientSocket);
    }
    close(serverSocket);
    return 0;
}
