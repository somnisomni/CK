#include "../common_bsd.h"

static const ushort SERVERPORT = 9000;
static const ushort BUFFERSIZE = 0b11111111;

int main(int argc, char *argv[]) {
  int retval = 0;

  SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) err_quit("소켓 생성 오류");

  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(SERVERPORT);

  retval = bind(sockfd, (const struct sockaddr *) &serveraddr, (const socklen_t) sizeof(serveraddr));
  if(retval < 0) err_quit("bind() 오류");

  cout << "*** UDP 서버 실행" << endl << endl;

  struct sockaddr_in clientaddr;
  socklen_t addrlen = 0;
  char buf[BUFFERSIZE + 1];
  while(true) {
    addrlen = sizeof(clientaddr);
    retval = recvfrom(sockfd, buf, BUFFERSIZE, 0, (struct sockaddr *)&clientaddr, &addrlen);
    if(retval < 0) {
      err_display("recvfrom() 오류");
      break;
    }

    buf[retval] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
    cout << "[UDP/" << addr << ":" << ntohs(clientaddr.sin_port) << "]";
    cout << " RECV (" << retval << " bytes): " << buf << endl;

    retval = sendto(sockfd, buf, retval, 0, (const struct sockaddr *)&clientaddr, addrlen);
    if(retval < 0) {
      err_display("sendto() 오류");
      break;
    }
  }

  close(sockfd);
  return 0;
}
