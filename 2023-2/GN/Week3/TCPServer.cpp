// ���� ��Ʈ��ũ ���� 3���� �ǽ��ڷ� 20230911
// û����ȭ������б� �������������� CMG
// �� ���� �ڷ� �� ���� �������� ���� �л��� �н� ���� �ܷ̿δ� ���� �� Ȱ���� �� �����ϴ�.

#include "..\common.h"

#define SERVERPORT 9000
#define BUFSIZE    512

int main(int argc, char *argv[]) {
  int retval;

  // ���� �ʱ�ȭ
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    return 1;

  // ���� ����
  SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(listen_sock == INVALID_SOCKET) err_quit("socket()");

  // bind()
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(SERVERPORT);
  retval = bind(listen_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(retval == SOCKET_ERROR) err_quit("bind()");

  // listen()
  retval = listen(listen_sock, SOMAXCONN);
  if(retval == SOCKET_ERROR) err_quit("listen()");

  printf("** Server is running **\n");

  // ������ ��ſ� ����� ����
  SOCKET client_sock;
  struct sockaddr_in clientaddr;
  int addrlen;
  char buf[BUFSIZE + 1];

  while(1) {
    // accept()
    addrlen = sizeof(clientaddr);
    client_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &addrlen);
    if(client_sock == INVALID_SOCKET) {
      err_display("accept()");
      break;
    }

    // ������ Ŭ���̾�Ʈ ���� ���
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
    printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
      addr, ntohs(clientaddr.sin_port));

    // Ŭ���̾�Ʈ�� ������ ���
    while(1) {
      // ������ �ޱ�
      retval = recv(client_sock, buf, BUFSIZE, 0);
      if(retval == SOCKET_ERROR) {
        err_display("recv()");
        break;
      } else if(retval == 0)
        break;

      // ���� ������ ���
      buf[retval] = '\0';
      printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

      // ������ ������
      retval = send(client_sock, buf, retval, 0);
      if(retval == SOCKET_ERROR) {
        err_display("send()");
        break;
      }
    }

    // ���� �ݱ�
    closesocket(client_sock);
    printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
      addr, ntohs(clientaddr.sin_port));
  }

  // ���� �ݱ�
  closesocket(listen_sock);

  // ���� ����
  WSACleanup();
  return 0;
}
