#include "../common_bsd.h"

static const char          *MULTICAST_IP = "236.36.36.36";
static const unsigned short REMOTEPORT   = 8888;
static const unsigned int   BUFFERSIZE   = 0b11111111;

int main(int argc, char *argv[]) {
  int retval = 0;

  // UDP socket creation
  SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) err_quit("소켓 생성 오류");

  // Skip reuseaddr option

  // Set socket option for multicast TTL
  int ttl = 3;
  retval = setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (const int *) &ttl, sizeof(ttl));
  if(retval < 0) err_quit("setsockopt() SO_REUSEADDR 오류");

  // Remote address setup
  struct sockaddr_in remoteaddr;
  memset(&remoteaddr, 0, sizeof(sockaddr_in));
  remoteaddr.sin_family = AF_INET;
  inet_pton(AF_INET, MULTICAST_IP, &remoteaddr.sin_addr);
  remoteaddr.sin_port = htons(REMOTEPORT);

  printf("*** UDP 멀티캐스트 센더 실행\n\n");

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

    retval = sendto(sockfd, buf, len, 0, (const struct sockaddr *)&remoteaddr, sizeof(remoteaddr));
    if(retval < 0) {
      err_display("sendto() 오류");
      break;
    }

    printf("[UDP MC Sender] %d 바이트 전송됨.\n", retval);
  }

  close(sockfd);
  return 0;
}
