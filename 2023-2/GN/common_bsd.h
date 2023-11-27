// 게임 네트워크 기초 3주차 실습자료
// 청강문화산업대학교 게임콘텐츠스쿨 CMG
// 본 수업 자료 및 관련 동영상은 수강 학생의 학습 목적 이외로는 배포 및 활용할 수 없습니다.

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
  cout << "오류: " << msg << endl;
}

void err_display(int errcode) {
  cout << "오류 코드: " << errcode << endl;
}

void err_quit(const char *msg) {
  err_display(msg);
  exit(1);
}
