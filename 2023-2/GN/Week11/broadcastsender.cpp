#include "..\common.h"

#define BROADCASTIP   "255.255.255.255"
#define BROADCASTPORT 9000
#define BUFFERSIZE    512

int main(int argc, char *argv[]) {
  int retval = 0;

  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    err_quit("Windows Socket API �ʱ�ȭ ����");

  SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock == INVALID_SOCKET) err_quit("���� ���� ����");

  // Socket option for enabling broadcast
  DWORD enable = 1;
  retval = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char *) &enable, sizeof(enable));
  if(retval == SOCKET_ERROR) err_quit("���� �ɼ� ���� ����");

  struct sockaddr_in remoteaddr;
  memset(&remoteaddr, 0, sizeof(sockaddr_in));
  remoteaddr.sin_family = AF_INET;
  inet_pton(AF_INET, BROADCASTIP, &remoteaddr.sin_addr);
  remoteaddr.sin_port = htons(BROADCASTPORT);

  printf("*** UDP ��ε�ĳ��Ʈ ���� ����\n\n");

  char buf[BUFFERSIZE + 1];
  int len = 0;
  while(true) {
    printf("\n[������ �Է�] > ");
    if(fgets(buf, BUFFERSIZE + 1, stdin) == NULL) {
      break;
    }
    len = strnlen(buf, BUFFERSIZE + 1);
    if(buf[len - 1] == '\n') buf[len - 1] = '\0';
    if(len == 0) break;

    retval = sendto(sock, buf, len, 0, (const struct sockaddr *)&remoteaddr, sizeof(remoteaddr));
    if(retval == SOCKET_ERROR) {
      err_display("sendto() ����");
      break;
    }

    printf("[UDP BC Sender] %d bytes sent.\n", retval);
  }

  closesocket(sock);
  WSACleanup();
  return 0;
}