#include "../common_bsd.h"

#define BUFSIZE 512
static const char *SERVERIP = "127.0.0.1";
static int SERVERPORT = 9000;

int main(int argc, char *argv[]) {
  int retval;
  if(argc > 1) {
    if(argv[1] != nullptr) SERVERIP = argv[1];
    if(argv[2] != nullptr) SERVERPORT = atoi(argv[2]);
  }

  printf(" * Server IP: %s\n", SERVERIP);
  printf(" * Server Port: %d\n", SERVERPORT);

  // Socket creation
  SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) err_quit("socket()");

  // connect
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
  serveraddr.sin_port = htons(SERVERPORT);

  retval = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(retval < 0) err_quit("connect()");

  printf(" * Client 프로그램이 Server 에 정상적으로 연결되었습니다. \n");

  // 데이터 통신에 사용할 변수
  char buf[BUFSIZE + 1];
  int len;
  while (1) {
    // 데이터 입력
    printf("\n[보낼 데이터] ");
    if(fgets(buf, BUFSIZE + 1, stdin) == NULL) break;

    // '\n' 문자 제거
    len = (int)strlen(buf);
    if(buf[len - 1] == '\n')
      buf[len - 1] = '\0';

    if(strlen(buf) == 0)
      break;

    // 데이터 보내기
    retval = send(sockfd, buf, (int)strlen(buf), 0);
    if(retval < 0) {
      err_display("send()");
      break;
    }

    printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);

    // 데이터 받기
    retval = recv(sockfd, buf, retval, MSG_WAITALL);
    if(retval <= 0) {
      err_display("recv()");
      break;
    } else if (retval == 0) break;

    // 받은 데이터 출력
    buf[retval] = '\0';
    printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
    printf("[받은 데이터] %s\n", buf);
  }

  // 소켓 닫기
  close(sockfd);

  return 0;
}
