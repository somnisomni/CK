#include <iostream>
#include "IOCompletionPort.h"
#include "PlayerInfo.pb.h"
#include "TestStorage.h"
using namespace std;
using namespace Week6Assignment;

const UINT16 SERVER_PORT = 11021;
const UINT16 MAX_CLIENT = 100;		//�� �����Ҽ� �ִ� Ŭ���̾�Ʈ ��

int main() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	TestStorage storage;
	IOCompletionPort ioCompletionPort(storage);

	//������ �ʱ�ȭ
	ioCompletionPort.InitSocket();

	//���ϰ� ���� �ּҸ� �����ϰ� ��� ��Ų��.
	ioCompletionPort.BindandListen(SERVER_PORT);

	// Test storage
	cout << "Players Info initialized" << endl;
	storage.PrintPlayersInfo();

	ioCompletionPort.StartServer(MAX_CLIENT);
	printf("�ƹ� Ű�� ���� ������ ����մϴ�\n");
	cout << endl << endl << "========================" << endl << endl;

	getchar();

	ioCompletionPort.DestroyThread();
	return 0;
}

