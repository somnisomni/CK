#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define TEST_DOMAIN "www.google.com"

int main() {
  // Socket initialization
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    return 1;
  }

  printf(" * Domain name = %s\n", TEST_DOMAIN);

  IN_ADDR addr;
  if(true /* GetIPAddress */) {
    printf(" * IP address = %s\n", "" /* inet_ntoa(addr) */);

    char name[256];
    if(true /* GetDomainName */) {
      printf(" * IP addr -> domain name = %s\n", "" /* name */);
    }
  }

  // Socket cleanup
  WSACleanup();

  return 0;
}