#include <iostream>
#include "IOCompletionPort.h"
#include "PlayerInfo.pb.h"
#include "TestStorage.h"
using namespace std;
using namespace Week6Assignment;

const UINT16 SERVER_PORT = 11021;
const UINT16 MAX_CLIENT = 100;		//총 접속할수 있는 클라이언트 수

int main() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	TestStorage storage;
	IOCompletionPort ioCompletionPort(storage);

	//소켓을 초기화
	ioCompletionPort.InitSocket();

	//소켓과 서버 주소를 연결하고 등록 시킨다.
	ioCompletionPort.BindandListen(SERVER_PORT);

	// Test storage
	cout << "Players Info initialized" << endl;
	storage.PrintPlayersInfo();

	ioCompletionPort.StartServer(MAX_CLIENT);
	printf("아무 키나 누를 때까지 대기합니다\n");
	cout << endl << endl << "========================" << endl << endl;

	getchar();

	ioCompletionPort.DestroyThread();
	return 0;
}

