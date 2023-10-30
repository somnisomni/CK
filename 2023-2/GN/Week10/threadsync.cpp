#include <cstdio>
#include <Windows.h>

#define lli long long int
#define MAX_COUNT 100000000

static lli count = 0L;
static CRITICAL_SECTION cs;

DWORD WINAPI ThreadCallbackPlus(LPVOID arg) {
  printf("[ Plus Thread ] Started. \n");

  for(int i = 0; i < MAX_COUNT; i++) {
    EnterCriticalSection(&cs);
    count += 2;
    LeaveCriticalSection(&cs);
  }

  printf("[ Plus Thread ] Finished. \n");
  return 0;
}

DWORD WINAPI ThreadCallbackMinus(LPVOID arg) {
  printf("[ Minus Thread ] Started. \n");

  for(int i = 0; i < MAX_COUNT; i++) {
    EnterCriticalSection(&cs);
    count -= 2;
    LeaveCriticalSection(&cs);
  }

  printf("[ Minus Thread ] Finished. \n");
  return 0;
}

int main(int argc, char *argv[]) {
  InitializeCriticalSection(&cs);

  printf("[ Main Thread ] count = %lld \n\n", count);

  HANDLE threads[] = {
    CreateThread(NULL, 0, ThreadCallbackPlus, NULL, CREATE_SUSPENDED, NULL),
    CreateThread(NULL, 0, ThreadCallbackMinus, NULL, CREATE_SUSPENDED, NULL)
  };

  printf("[ Main Thread ] 2 threads created. \n");

  printf("[ Main Thread ] Threads start. \n");
  ResumeThread(threads[0]);
  ResumeThread(threads[1]);

  printf("[ Main Thread ] Wait for threads to be finished ... \n\n");
  WaitForMultipleObjects(2, threads, TRUE, INFINITE);
  
  printf("\n[ Main Thread ] Threads finished. \n");
  printf("[ Main Thread ] count = %lld \n", count);

  DeleteCriticalSection(&cs);
  return 0;
}
