#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8443

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Binding failed");
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        client_len = sizeof(client_addr);

        // Accept a new client connection
        newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (newsockfd < 0) {
            error("Error accepting connection");
        }

        // Receive data from the client (Student ID)
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(newsockfd, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            error("Error receiving data from client");
        }

        // Print the received Student ID
        printf("Received Student ID from client: %s\n", buffer);

        // Respond to the client
        const char *response_message = "Thank you for sending your Student ID.";
        if (send(newsockfd, response_message, strlen(response_message), 0) < 0) {
            error("Error sending response to client");
        }

        // Close the connection with the current client
        close(newsockfd);
    }

    // Close the server socket
    close(sockfd);

    return 0;
}

