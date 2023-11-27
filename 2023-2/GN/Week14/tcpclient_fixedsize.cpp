#include "../common_bsd.h"

#define BUFSIZE 50
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
  const char *testdata[] = {
    "안녕하세요",
    "반가워요",
    "오늘따라 할 이야기가 많을 것 같네요",
    "저도 그렇네요",
  };

  // 서버와 데이터 통신
  for(int i = 0; i < 4; i++) {
    // 데이터 입력(시뮬레이션)
    memset(buf, '#', sizeof(buf));
    strncpy(buf, testdata[i], strlen(testdata[i]));

    // 데이터 보내기
    retval = send(sockfd, buf, BUFSIZE, 0);
    if(retval < 0) {
      err_display("send()");
      break;
    }

    printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);
  }

  // 소켓 닫기
  close(sockfd);

  return 0;
}
