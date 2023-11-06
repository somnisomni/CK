#include "..\common.h"

#define SERVERPORT 9000
#define BUFFERSIZE 512

int main(int argc, char *argv[]) {
  int retval = 0;

  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    err_quit("Windows Socket API 초기화 오류");

  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock == INVALID_SOCKET) err_quit("소켓 생성 오류");

  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(SERVERPORT);
  
  retval = bind(sock, (const struct sockaddr *) &serveraddr, sizeof(serveraddr));
  if(retval == SOCKET_ERROR) err_quit("bind() 오류");

  printf("*** UDP 서버 실행\n\n");

  struct sockaddr_in clientaddr;
  int addrlen = 0;
  char buf[BUFFERSIZE + 1];
  while(true) {
    addrlen = sizeof(clientaddr);
    retval = recvfrom(sock, buf, BUFFERSIZE, 0, (struct sockaddr *)&clientaddr, &addrlen);
    if(retval == SOCKET_ERROR) {
      err_display("recvfrom() 오류");
      break;
    }

    buf[retval] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
    printf("[UDP/%s:%d] RECV (%d bytes): %s\n", addr, ntohs(clientaddr.sin_port), retval, buf);

    retval = sendto(sock, buf, retval, 0, (const struct sockaddr *)&clientaddr, addrlen);
    if(retval == SOCKET_ERROR) {
      err_display("sendto() 오류");
      break;
    }
  }

  closesocket(sock);
  WSACleanup();
  return 0;
}