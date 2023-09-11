// ���� ��Ʈ��ũ ���� 3���� �ǽ��ڷ� 20230911
// û����ȭ������б� �������������� CMG
// �� ���� �ڷ� �� ���� �������� ���� �л��� �н� ���� �ܷ̿δ� ���� �� Ȱ���� �� �����ϴ�.

#include "..\common.h"

char *SERVERIP = (char *)"127.0.0.1";
#define SERVERPORT 9999
#define BUFSIZE    512

int main(int argc, char *argv[]) {
  int retval;

  // ����� �μ��� ������ IP �ּҷ� ���
  if(argc > 1) SERVERIP = argv[1];

  // ���� �ʱ�ȭ
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    return 1;

  // ���� ����
  printf("Creating socket...\n");
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock == INVALID_SOCKET) err_quit("socket()");

  // connect()
  printf("Connecting...\n");
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
  serveraddr.sin_port = htons(SERVERPORT);
  retval = connect(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(retval == SOCKET_ERROR) err_quit("connect()");

  printf("** Connected to server **\n");

  // ������ ��ſ� ����� ����
  char buf[BUFSIZE + 1];
  int len;

  // ������ ������ ���
  while(1) {
    // ������ �Է�
    printf("\n[���� ������] ");
    if(fgets(buf, BUFSIZE + 1, stdin) == NULL)
      break;

    // '\n' ���� ����
    len = (int)strlen(buf);
    if(buf[len - 1] == '\n')
      buf[len - 1] = '\0';
    if(strlen(buf) == 0)
      break;

    // ������ ������
    retval = send(sock, buf, (int)strlen(buf), 0);
    if(retval == SOCKET_ERROR) {
      err_display("send()");
      break;
    }
    printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

    // ������ �ޱ�
    retval = recv(sock, buf, retval, MSG_WAITALL);
    if(retval == SOCKET_ERROR) {
      err_display("recv()");
      break;
    } else if(retval == 0)
      break;

    // ���� ������ ���
    buf[retval] = '\0';
    printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
    printf("[���� ������] %s\n", buf);
  }

  // ���� �ݱ�
  closesocket(sock);

  // ���� ����
  WSACleanup();
  return 0;
}
