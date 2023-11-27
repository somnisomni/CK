#include "../common_bsd.h"

#define BUFSIZE 512
static int SERVERPORT = 9000;

int main(int argc, char *argv[]) {
  int retval;

  printf(" * Server Port: %d\n", SERVERPORT);

  // Socket creation
  SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
  if(listenSock < 0) err_quit("socket()");

  // bind()
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(SERVERPORT);

  retval = bind(listenSock, (const struct sockaddr *)&serveraddr, (const socklen_t) sizeof(serveraddr));
  if (retval < 0) err_quit("bind()");

  // listen()
  retval = listen(listenSock, SOMAXCONN);
  if(retval < 0) err_quit("listen()");

  printf(" * Echo Server 가 정상 동작을 시작했습니다. \n");

  // 데이터 통신에 사용할 변수
  SOCKET clientSock;
  struct sockaddr_in clientaddr;
  int addrlen;
  char buf[BUFSIZE + 1];
  while(1) {
    // accept()
    addrlen = sizeof(clientaddr);
    clientSock = accept(listenSock, (sockaddr *)&clientaddr, (socklen_t *) &addrlen);
    if(clientSock < 0) {
      err_display("accept()");
      break;
    }

    // 접속한 클라이언트 정보 출력
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
    printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n", addr, ntohs(clientaddr.sin_port));

    // 클라이언트와 데이터 통신
    while(1) {
      // 데이터 받기
      retval = recv(clientSock, buf, BUFSIZE, 0);
      if(retval < 0) {
        err_display("recv()");
        break;
      } else if (retval == 0)
        break;

      // 받은 데이터 출력
      buf[retval] = '\0';
      printf("[TCP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

      // 데이터 보내기
      retval = send(clientSock, buf, retval, 0);
      if (retval < 0) {
        err_display("send()");
        break;
      }
    }

    // 소켓 닫기
    close(clientSock);
    printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n", addr, ntohs(clientaddr.sin_port));
  }

  // 소켓 닫기

  close(listenSock);

  return 0;
}
