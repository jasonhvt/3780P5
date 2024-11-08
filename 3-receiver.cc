#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <port> [-4 | -6]" << std::endl;
        return 1;
    }

    int sock;
    struct addrinfo hints{}, *res, *p;
    int rv;

    // Determine the address family based on the argument
    int address_family = AF_UNSPEC; // Default: support both IPv4 and IPv6
    if (argc == 3) {
        if (std::string(argv[2]) == "-4") {
            address_family = AF_INET; // IPv4 only
        } else if (std::string(argv[2]) == "-6") {
            address_family = AF_INET6; // IPv6 only
        } else {
            std::cerr << "Invalid argument: " << argv[2] << std::endl;
            return 1;
        }
    }

    // Setting up hints for getaddrinfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = address_family; // Use specified address family
    hints.ai_socktype = SOCK_DGRAM;   // UDP
    hints.ai_flags = AI_PASSIVE;      // Use local IP

    if ((rv = getaddrinfo(nullptr, argv[1], &hints, &res)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        return 1;
    }

    // Loop through all the results and bind to the first we can
    for (p = res; p != nullptr; p = p->ai_next) {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock);
            perror("bind");
            continue;
        }

        break;
    }

    if (p == nullptr) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 2;
    }

    freeaddrinfo(res);

    std::cout << "Waiting for a message..." << std::endl;

    char buffer[512];
    struct sockaddr_storage senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    // Receive a message
    ssize_t bytesReceived = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, 
                                     (struct sockaddr*)&senderAddr, &senderAddrLen);
    if (bytesReceived == -1) {
        perror("recvfrom");
        close(sock);
        return 3;
    }

    buffer[bytesReceived] = '\0';  // Null-terminate the received message
    std::cout << "Received: " << buffer << std::endl;

    // Send the same message back to the sender
    ssize_t bytesSent = sendto(sock, buffer, bytesReceived, 0, 
                               (struct sockaddr*)&senderAddr, senderAddrLen);
    if (bytesSent == -1) {
        perror("sendto");
        close(sock);
        return 4;
    }

    std::cout << "Message sent back to sender" << std::endl;

    close(sock);
    return 0;
}

