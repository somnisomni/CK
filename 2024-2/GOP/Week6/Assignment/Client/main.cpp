#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "PlayerInfo.pb.h"
using namespace std;
using namespace Week6Assignment;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "11021"

static bool RUNNING = true;

int sendMessage(SOCKET socket, google::protobuf::Message& message) {
	cout << "SEND protobuf: " << message.DebugString() << endl;
	return send(socket, message.SerializeAsString().c_str(), message.ByteSizeLong(), 0);
}

void recvThread(SOCKET socket) {
    //// Send all players info request on initial connection
    //WrappedRequestMessage request;
    //request.mutable_allplayersinforequest();
    //sendMessage(socket, request);

    // Loop
    while (RUNNING) {
        char recvbuf[DEFAULT_BUFLEN];
        int bytesRecv;

        // printf("recv() - Receive until the peer closes the connection\n");
        bytesRecv = recv(socket, recvbuf, DEFAULT_BUFLEN, 0);
        if(bytesRecv > 0) {
			recvbuf[bytesRecv] = '\0';

            printf("Bytes received: %d\n", bytesRecv);
            // cout << "Received: " << recvbuf << endl;

			// Parse protobuf
			WrappedResponseMessage response;
			response.ParseFromString(recvbuf);
            cout << "RECV protobuf: " << response.DebugString() << endl;

            // Process protobuf message
			if (response.has_allplayersinforesponse()) {
				cout << "AllPlayersInfoResponse received" << endl;
			} else if (response.has_playerinforesponse()) {
				cout << "PlayerInfoResponse received" << endl;
			} else if (response.has_playerinventoryresponse()) {
				cout << "PlayerInventoryResponse received" << endl;
            } else if (response.has_errorresponse()) {
				cout << "ErrorResponse received" << endl;
			} else {
				cout << "Unknown message received" << endl;
			}
            cout << endl;
        } else if(bytesRecv == 0) {
            printf("Connection closed\n");
            RUNNING = false;
            return;
        } else {
            const int lastError = ::WSAGetLastError();

            if(lastError == WSAEWOULDBLOCK) {
                //printf("recv failed with WSAEWOULDBLOCK(%d)\n", lastError);
                Sleep(1000 / 60);
                continue;
            }

            printf("recv failed with error: %d\n", lastError);
            RUNNING = false;
            break;
        }
    }
}

void inputThread(SOCKET socket) {
    cout << endl;
	cout << "=== Valid inputs ===" << endl;
	cout << "p<id> - Individual player info" << endl;
	cout << "i<id> - Individual player inventory" << endl;
	cout << "a - All players info" << endl;
	cout << "q - Quit" << endl;
    cout << "====================" << endl << endl;

    while (RUNNING) {
        string input;
		cin >> input;

        if (input.length() <= 0) continue;

        WrappedRequestMessage request;
        switch (input[0]) {
            case 'p': {
                // Individual player info
                if (input.length() <= 1) {
					cout << "Need player id" << endl;
                    continue;
                }

                int idx = stoi(input.substr(1));

				PlayerInfoRequest req;
				req.set_id(idx);
				request.mutable_playerinforequest()->CopyFrom(req);
				break;
            }
            case 'i': {
                // Individual player inventory
                if (input.length() <= 1) {
                    cout << "Need player id" << endl;
                    continue;
                }

                int idx = stoi(input.substr(1));

                PlayerInventoryRequest req;
                req.set_id(idx);
                request.mutable_playerinventoryrequest()->CopyFrom(req);
                break;
            }
            case 'a': {
                // All players info
                request.mutable_allplayersinforequest();
                break;
            }
            case 'q': {
                cout << endl << " Quit " << endl;
				RUNNING = false;
                return;
            }
            default:
				cout << "Invalid input" << endl;
                continue;
        }

        int result = sendMessage(socket, request);
        if (result == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            RUNNING = false;
            return;
        }

        printf("Bytes Sent: %ld\n", result);
    }
}

int __cdecl main(int argc, char** argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    printf("WSAStartup() -  Initialize Winsock\n");
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        printf("socket() - Create a client SOCKET\n");
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        printf("connect() - Connect to server\n");
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // nonblock socket setting
    u_long on = 1;
    ::ioctlsocket(ConnectSocket, FIONBIO, &on);

    // Start recv/input thread
    thread recvTh(recvThread, ConnectSocket);
	thread inputTh(inputThread, ConnectSocket);

    recvTh.join();
	inputTh.join();

    // cleanup
    printf("closesocket(); WSACleanup() - cleanup\n");
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}