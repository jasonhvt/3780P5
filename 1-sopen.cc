#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock;

  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    std::cerr << "Error opening socket" << std::endl;
    return 1;
  }

  close(sock);
}
