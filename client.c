#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Step 1: Create a socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Set up server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Send data to server
    char message[] = "Hello from client";
    sendto(client_socket, (const char*)message, strlen(message), 0, (const struct sockaddr*)&server_address, sizeof(server_address));

    // Step 4: Receive and print the response
    char buffer[1024];
    int n, len;

    len = sizeof(server_address);
    n = recvfrom(client_socket, (char*)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&server_address, &len);
    buffer[n] = '\0';

    printf("Server: %s\n", buffer);

    // Step 5: Close the socket
    close(client_socket);

    return 0;
}
