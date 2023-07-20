#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888

int main() {
    int clientSocket;
    struct sockaddr_in server_addr;
    int randomNumber;

    // Create a TCP socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Could not create socket");
        exit(1);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, "192.168.80.128", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(clientSocket);
        exit(1);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(clientSocket);
        exit(1);
    }

    // Receive the random number from the server
    recv(clientSocket, &randomNumber, sizeof(randomNumber), 0);
    printf("Received random number from server: %d\n", randomNumber);
    close(clientSocket);
    return 0;
}
