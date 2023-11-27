// ���� ��Ʈ��ũ ���� 3���� �ǽ��ڷ�
// û����ȭ������б� �������������� CMG
// �� ���� �ڷ� �� ���� �������� ���� �л��� �н� ���� �ܷ̿δ� ���� �� Ȱ���� �� �����ϴ�.

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
using namespace std;

typedef int SOCKET;
#define packedstruct struct __attribute__((packed))
#define issockerr(x) (x < 0)

void err_display(const char *msg) {
  cout << "����: " << msg << endl;
}

void err_display(int errcode) {
  cout << "���� �ڵ�: " << errcode << endl;
}

void err_quit(const char *msg) {
  err_display(msg);
  exit(1);
}
