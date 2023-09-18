#pragma comment(lib, "ws2_32")

#include <cstdio>
#include <WinSock2.h>

int main() {
  // Socket initialization
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    return 1;
  }

  unsigned short x1 = 0x1234;
  unsigned long y1 = 0x12345678;
  unsigned short x2;
  unsigned long y2;

  printf("[Host Bytes to Network Bytes]\n");
  printf("0x%x => 0x%x \n", x1, x2 = htons(x1));
  printf("0x%x => 0x%x \n\n", y1, y2 = htonl(y1));

  printf("[Network Bytes to Host Bytes]\n");
  printf("0x%x => 0x%x \n", x2, ntohs(x2));
  printf("0x%x => 0x%x \n\n", y2, ntohl(y2));

  // Socket cleanup
  WSACleanup();

  return 0;
}