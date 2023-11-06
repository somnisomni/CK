#include "..\common.h"

#define SERVERPORT 9000
#define BUFFERSIZE 512

int main(int argc, char *argv[]) {
  int retval = 0;

  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    err_quit("Windows Socket API �ʱ�ȭ ����");

  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock == INVALID_SOCKET) err_quit("���� ���� ����");

  struct sockaddr_in localaddr;
  memset(&localaddr, 0, sizeof(sockaddr_in));
  localaddr.sin_family = AF_INET;
  localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localaddr.sin_port = htons(SERVERPORT);

  retval = bind(sock, (const struct sockaddr *)&localaddr, sizeof(localaddr));
  if(retval == SOCKET_ERROR) err_quit("bind() ����");

  printf("*** UDP ��ε�ĳ��Ʈ ���ù� ����\n\n");

  struct sockaddr_in peeraddr;
  int addrlen = 0;
  char buf[BUFFERSIZE + 1];
  while(true) {
    addrlen = sizeof(peeraddr);
    retval = recvfrom(sock, buf, BUFFERSIZE, 0, (struct sockaddr *)&peeraddr, &addrlen);
    if(retval == SOCKET_ERROR) {
      err_display("recvfrom() ����");
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