#include "..\common.h"

#define SERVER_PORT 9000
#define BUFFER_SIZE 1024

char *SERVER_IP = (char *)"127.0.0.1";

int main(int argc, char *argv[]) {
  int retval = 0;

  // Startup
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    err_quit("WSA startup failed");
  }

  // Socket creation
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock == INVALID_SOCKET) {
    err_quit("Socket creation failed");
  }

  // Connect
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);
  serverAddr.sin_port = htons(SERVER_PORT);

  retval = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(retval == SOCKET_ERROR) {
    err_quit("Connect failed");
  }

  printf(" * Connected to server !\n");

  // Communicate with server
  char buf[BUFFER_SIZE + 1];

  while(true) {
    // Input data
    printf("\n[Input data] > ");
    if(fgets(buf, BUFFER_SIZE + 1, stdin) == NULL) break;

    // Normalize input data
    int len = (int)strnlen(buf, BUFFER_SIZE + 1);
    if(len == 0) break;
    if(buf[len - 1] == '\n') buf[len - 1] = '\0';

    // Send user data to server
    retval = send(sock, buf, len, 0);
    if(retval == SOCKET_ERROR) {
      err_display("Send data to server failed");
      break;
    }
    printf("* %d bytes sent\n", retval);

    // Receive data
    retval = recv(sock, buf, retval, MSG_WAITALL);
    if(retval == SOCKET_ERROR) {
      err_display("Receive data from server failed");
      break;
    } else if(retval == 0) {
      printf("* Server connection closed normally");
      break;
    }

    // Print received data
    buf[retval] = '\0';
    printf("* %d bytes received\n", retval);
    printf("[Recv] %s\n", buf);
  }

  // Cleanup
  closesocket(sock);
  WSACleanup();

  return 0;
}
