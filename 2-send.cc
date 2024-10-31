#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 512
#define PORT "3000"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <destination_host>" << std::endl;
        return 1;
    }

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    // Set up hints struct for address lookup
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_DGRAM;  // UDP

    // Get address info for the destination host and port
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        return 1;
    }

    // Loop through the results and connect to the first valid one
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Socket creation failed");
            continue;
        }
        break;
    }

    if (p == nullptr) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Send message to server
    const char *message = "Hello, World!";
    if (sendto(sockfd, message, strlen(message), 0, p->ai_addr, p->ai_addrlen) == -1) {
        perror("sendto failed");
        close(sockfd);
        freeaddrinfo(servinfo);
        return 1;
    }
    std::cout << "Message sent: " << message << std::endl;

    // Clean up
    close(sockfd);
    freeaddrinfo(servinfo);
    return 0;
}
