#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <destination_host> <destination_port>" << std::endl;
        return 1;
    }

    int sock;
    struct addrinfo hints{}, *res, *p;
    int rv;

    // Setting up hints for getaddrinfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    // Either IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // UDP

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
        return 1;
    }

    // Loop through all the results and bind to the first we can
    for (p = res; p != nullptr; p = p->ai_next) {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }
        break;
    }

    if (p == nullptr) {
        std::cerr << "Failed to create socket" << std::endl;
        return 2;
    }

    // Sending message to the receiver
    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    int bytes_sent = sendto(sock, message.c_str(), message.size(), 0, p->ai_addr, p->ai_addrlen);
    if (bytes_sent == -1) {
        perror("sendto");
        close(sock);
        return 3;
    }

    // Buffer to hold the reply
    char buffer[512];
    memset(buffer, 0, sizeof buffer);
    socklen_t addr_len = p->ai_addrlen;

    // Receiving reply from the receiver
    int bytes_received = recvfrom(sock, buffer, sizeof buffer - 1, 0, p->ai_addr, &addr_len);
    if (bytes_received == -1) {
        perror("recvfrom");
        close(sock);
        return 4;
    }

    // Null-terminate and display the reply
    buffer[bytes_received] = '\0';
    std::cout << "Received reply: " << buffer << std::endl;

    freeaddrinfo(res);
    close(sock);
    return 0;
}

