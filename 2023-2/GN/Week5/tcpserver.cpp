#include "..\common.h"

#define SERVER_PORT 9000
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  int retval = 0;

  // Startup
  WSADATA wsa;
  if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    err_quit("WSA startup failed");
  }

  // Socket creation
  SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
  if(listenSock == INVALID_SOCKET) {
    err_quit("Socket creation failed");
  }

  // Bind
  struct sockaddr_in listenAddr;
  memset(&listenAddr, 0, sizeof(listenAddr));
  listenAddr.sin_family = AF_INET;
  listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  listenAddr.sin_port = htons(SERVER_PORT);

  retval = bind(listenSock, (struct sockaddr *) &listenAddr, sizeof(listenAddr));
  if(retval == SOCKET_ERROR) {
    err_quit("Socket bind failed");
  }

  // Listen
  retval = listen(listenSock, SOMAXCONN);
  if(retval == SOCKET_ERROR) {
    err_quit("Listen failed");
  }

  printf(" * Echo Server is running properly !\n");

  // Communicate with client
  SOCKET clientSock;
  struct sockaddr_in clientAddr;
  int addrLen = sizeof(clientAddr);
  char buf[BUFFER_SIZE + 1];
 
  while(true) {
    // Client accept
    clientSock = accept(listenSock, (struct sockaddr *)&clientAddr, &addrLen);
    if(clientSock == INVALID_SOCKET) {
      err_display("Client socket error");
      break;
    }

    // Print connected client info
    char addr[INET_ADDRSTRLEN];
    unsigned short port = ntohs(clientAddr.sin_port);
    inet_ntop(AF_INET, &clientAddr.sin_addr, addr, sizeof(addr));
    printf("[TCP Server] Client connected (%s:%d)\n", addr, port);

    // Communicate
    while(true) {
      // Receive data
      retval = recv(clientSock, buf, BUFFER_SIZE, 0);
      if(retval == SOCKET_ERROR) {
        err_display("Receive data from client failed");
        break;
      } else if(retval == 0) {
        printf("[TCP Server] Client connection closed normally (%s:%d)\n", addr, port);
        break;
      }

      // Print received data
      buf[retval] = '\0';
      printf("[TCP IN %s:%d] %s\n", addr, port, buf);

      // Send(Echo) received data to client
      retval = send(clientSock, buf, retval, 0);
      if(retval == SOCKET_ERROR) {
        err_display("Send data to client failed");
        break;
      }
    }

    // Client socket cleanup
    closesocket(clientSock);
    printf("[TCP Server] Connection closed with client (%s:%d)\n", addr, port);
  }

  // Cleanup
  closesocket(listenSock);
  WSACleanup();

  return 0;
}
