#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main() {
  // Socket initialization
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    return 1;
  }

  const char *ipv4 = "192.168.30.84";
  printf("IPv4 Address (before convert) = %s\n", ipv4);
  printf("IPv4 Address (after convert)  = 0x%x\n", inet_addr(ipv4));

  IN_ADDR ipv4Num;
  ipv4Num.s_addr = inet_addr(ipv4);
  printf("IPv4 Address (re-convert)     = %s\n", inet_ntoa(ipv4Num));
  printf("\n");

  // Socket cleanup
  WSACleanup();

  return 0;
}