#include "..\common.h"

const static char *SERVERIP = "127.0.0.1";
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
  inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
  serveraddr.sin_port = htons(SERVERPORT);

  printf("*** UDP 클라이언트 실행\n\n");

  struct sockaddr_in peeraddr;
  int addrlen = 0;
  char buf[BUFFERSIZE + 1];
  int len = 0;
  while(true) {
    printf("\n[데이터 입력] > ");
    if(fgets(buf, BUFFERSIZE + 1, stdin) == NULL) {
      break;
    }
    len = strnlen(buf, BUFFERSIZE + 1);
    if(buf[len - 1] == '\n') buf[len - 1] = '\0';
    if(len == 0) break;
    
    retval = sendto(sock, buf, len, 0, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(retval == SOCKET_ERROR) {
      err_display("sendto() 오류");
      break;
    }

    printf("[UDP Client] %d bytes sent.\n", retval);

    addrlen = sizeof(peeraddr);
    retval = recvfrom(sock, buf, BUFFERSIZE, 0, (struct sockaddr *)&peeraddr, &addrlen);
    if(retval == SOCKET_ERROR) {
      err_display("recvfrom() 오류");
      break;
    }

    if(memcmp(&peeraddr, &serveraddr, sizeof(peeraddr))) {
      printf("[UDP Client] Received data from wrong source!\n");
      break;
    }

    buf[retval] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));
    printf("[UDP/%s:%d] RECV (%d bytes): %s\n", addr, ntohs(peeraddr.sin_port), retval, buf);
  }

  closesocket(sock);
  WSACleanup();
  return 0;
}