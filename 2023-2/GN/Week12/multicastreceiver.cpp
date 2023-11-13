#include "../common_bsd.h"

static const char          *MULTICAST_IP = "236.36.36.36";
static const unsigned short LOCALPORT    = 8888;
static const unsigned int   BUFFERSIZE   = 0b11111111;

int main(int argc, char *argv[]) {
  int retval = 0;

  // UDP socket creation
  SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) err_quit("소켓 생성 오류");

  // Set socket option (reuse address)
  int optval = 1;
  retval = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const int *) &optval, (const socklen_t) sizeof(optval));
  if(retval < 0) err_quit("setsockopt() SO_REUSEADDR 오류");

  // Bind
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(LOCALPORT);

  retval = bind(sockfd, (const struct sockaddr *) &serveraddr, (const socklen_t) sizeof(serveraddr));
  if(retval < 0) err_quit("bind() 오류");

  // Join multicast group
  struct ip_mreq mreq;
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
  retval = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *) &mreq, sizeof(mreq));
  if(retval < 0) err_quit("setsockopt() IP_ADD_MEMBERSHIP 오류");

  cout << "*** UDP 멀티캐스트 리시버 실행" << endl << endl;

  struct sockaddr_in peeraddr;
  socklen_t addrlen = 0;
  char buf[BUFFERSIZE + 1];
  while(true) {
    addrlen = sizeof(peeraddr);
    retval = recvfrom(sockfd, buf, BUFFERSIZE, 0, (struct sockaddr *) &peeraddr, &addrlen);
    if(retval < 0) {
      err_display("recvfrom() 오류");
      break;
    }

    buf[retval] = '\0';
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));
    printf("[UDP/%s:%d] RECV (%d bytes): %s\n", addr, ntohs(peeraddr.sin_port), retval, buf);
  }

  retval = setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char *) &mreq, sizeof(mreq));
  if(retval < 0) err_quit("setsockopt() IP_DROP_MEMBERSHIP 오류");

  close(sockfd);
  return 0;
}
