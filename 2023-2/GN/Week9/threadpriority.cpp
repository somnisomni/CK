#include <cstdio>
#include <Windows.h>

DWORD WINAPI ThreadCallback(LPVOID obj) {
  while(1);
  return 0;
}

int main() {
  printf("Main Thread\n");
  printf("  Priorities: %d ~ %d\n\n", THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);

  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);

  for(int i = 0; i < sysinfo.dwNumberOfProcessors; i++) {
    printf(" Thread #%d start\n", i);
    HANDLE thread = CreateThread(NULL, 0, ThreadCallback, NULL, 0, NULL);
    SetThreadPriority(thread, THREAD_PRIORITY_BELOW_NORMAL);
    CloseHandle(thread);
  }

  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
  Sleep(1000);
  printf("\n Main thread again \n");

  return 0;
}