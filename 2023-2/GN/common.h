// 게임 네트워크 기초 3주차 실습자료
// 청강문화산업대학교 게임콘텐츠스쿨 CMG
// 본 수업 자료 및 관련 동영상은 수강 학생의 학습 목적 이외로는 배포 및 활용할 수 없습니다.

#pragma once

#define	_CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32")

void err_quit(const char *msg) {
  LPVOID lpMsgBuf;
  FormatMessageA(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL, WSAGetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (char *)&lpMsgBuf, 0, NULL
  );
  MessageBoxA(NULL, (const char *)lpMsgBuf, msg, MB_ICONERROR);
  LocalFree(lpMsgBuf);
  exit(1);
}

void err_display(const char *msg) {
  LPVOID lpMsgBuf;
  FormatMessageA(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL, WSAGetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (char *)&lpMsgBuf, 0, NULL
  );
  printf("[%s] %s\n", msg, (char *)lpMsgBuf);
  LocalFree(lpMsgBuf);
}

void err_display(int errcode) {
  LPVOID lpMsgBuf;
  FormatMessageA(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL, errcode,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (char *)&lpMsgBuf, 0, NULL
  );
  printf("[오류] %s\n", (char *)lpMsgBuf);
  LocalFree(lpMsgBuf);
}
