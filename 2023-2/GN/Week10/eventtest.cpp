#include <cstdio>
#include <Windows.h>

#define BUFFERSIZE 0b1111

static HANDLE writeEvent;
static HANDLE readEvent;
int buf[BUFFERSIZE];

DWORD WINAPI WriteThread(LPVOID arg) {
  printf("[ Write Thread (%5d) ] Started. \n", GetCurrentThreadId());

  DWORD retval;
  for(int k = 1; k <= 500; k++) {
    retval = WaitForSingleObject(readEvent, INFINITE);
    if(retval != WAIT_OBJECT_0) break;

    for(int i = 0; i < BUFFERSIZE; i++) {
      buf[i] = k;
    }

    SetEvent(writeEvent);
  }

  printf("[ Write Thread (%5d) ] Finished. \n", GetCurrentThreadId());
  return 0;
}

DWORD WINAPI ReadThread(LPVOID arg) {
  printf("[ Read  Thread (%5d) ] Started. \n", GetCurrentThreadId());

  DWORD retval;
  while(TRUE) {
    retval = WaitForSingleObject(writeEvent, INFINITE);
    if(retval != WAIT_OBJECT_0) break;

    printf("[ Read  Thread (%5d) ] read: ", GetCurrentThreadId());
    for(int i = 0; i < BUFFERSIZE; i++) printf("%3d ", buf[i]);
    printf("\n");

    memset(buf, 0, BUFFERSIZE);
    SetEvent(readEvent);
  }

  printf("[ Read  Thread (%5d) ] Finished. \n", GetCurrentThreadId());
  return 0;
}

int main(int argc, char *argv[]) {
  writeEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  readEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  printf("[ Main Thread] Events created. \n");

  HANDLE threads[] = {
    CreateThread(NULL, 0, WriteThread, NULL, CREATE_SUSPENDED, NULL),
    CreateThread(NULL, 0, ReadThread, NULL, CREATE_SUSPENDED, NULL),
    CreateThread(NULL, 0, ReadThread, NULL, CREATE_SUSPENDED, NULL)
  };
  printf("[ Main Thread ] 3 threads created. \n");

  printf("[ Main Thread ] Starting threads ... \n\n");
  ResumeThread(threads[0]);
  ResumeThread(threads[1]);
  ResumeThread(threads[2]);

  printf("[ Main Thread ] Sending read event ... \n");
  SetEvent(readEvent);

  printf("[ Main Thread ] Wait for threads to be finished ... \n\n");
  WaitForMultipleObjects(3, threads, TRUE, INFINITE);

  printf("\n[ Main Thread ] Threads finished. \n");

  CloseHandle(writeEvent);
  CloseHandle(readEvent);
  return 0;
}
