// Steps to Understand:
// Server Side:
// Socket Creation (socket):

// Creates a socket for communication.
// Server Address Setup:

// Defines the server's address using a sockaddr_in structure.
// Bind the Socket (bind):

// Associates the socket with a specific address and port.
// Receive Data (recvfrom):

// Waits for data from a client and receives it.
// Send Data (sendto):

// Sends a response back to the client.
// Close the Socket (close):

// Releases the resources associated with the socket.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Step 1: Create a socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0); 
    /*
    Definition: int socket(int domain, int type, int protocol);
    Parameters:
    domain: Specifies the communication domain (e.g., AF_INET for IPv4).
    type: Specifies the socket type (e.g., SOCK_DGRAM for UDP).
    protocol: Specifies the protocol to be used (0 for default protocol).
    Return Type: int
    Description: Creates a new socket.
    */
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Set up server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // Step 3: Bind the socket
    if (bind(server_socket, (const struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    /*
    bind Function:
    Definition: int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    Parameters:
    sockfd: Socket file descriptor.
    addr: Pointer to a struct sockaddr containing the details of the local address.
    addrlen: Size of the address structure.
    Return Type: int
    Description: Associates a socket with a specific address and port.
    */

    // Step 4: Receive and print data
    char buffer[1024];
    int len, n;

    len = sizeof(server_address);
    n = recvfrom(server_socket, (char*)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&server_address, &len);
    buffer[n] = '\0';
    /*
    recvfrom Function:
    Description: Receives a message from a socket and stores the source address.
    Parameters:
    sockfd: Socket file descriptor.
    buf: Buffer to store the received data.
    len: Maximum length of the buffer.
    flags: Flags for message reception.
    src_addr: Pointer to a struct sockaddr to store the source address.
    addrlen: Pointer to the size of the source address structure.
    Return Type: ssize_t
    */

    printf("Client: %s\n", buffer);

    // Step 5: Send a response
    char message[] = "Hello from server";
    sendto(server_socket, (const char*)message, strlen(message), 0, (const struct sockaddr*)&server_address, sizeof(server_address));
    /*
    sendto Function:
    Description: Sends a message to a specified socket address.    
    Parameters:
    sockfd: Socket file descriptor.
    buf: Buffer containing the data to be sent.
    len: Length of the data.
    flags: Flags for message transmission.
    dest_addr: Pointer to a struct sockaddr containing the destination address.
    addrlen: Size of the destination address structure.
    Return Type: ssize_t
    
    */

    // Step 6: Close the socket
    close(server_socket);
    /*
    close Function:
    Description: Closes a socket.

    Parameters:
    sockfd: Socket file descriptor to be closed.
    Return Type: int
    */

    return 0;
}
