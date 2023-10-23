#include <cstdio>
#include <ctime>
#include <Windows.h>

static long long int sum = 0L;

DWORD WINAPI ThreadCallback(LPVOID arg) {
  long long int num = (long long int)arg;

  printf("[ Child Thread ] start calculation \n");
  for(long long int i = 1; i <= num; i++) {
    sum += i;
  }
  printf("[ Child Thread ] end calculation \n");

  return 0;
}

int main() {
  long long int num = 3456789010L;

  HANDLE thread = CreateThread(NULL, 0, ThreadCallback, (LPVOID)(long long int) num, CREATE_SUSPENDED, NULL);
  printf("[ Main Thread ] Child thread created in suspended status. \n");
  printf("[ Main Thread ] sum = %lld \n", sum);

  time_t t1 = time(NULL);
  printf("[ Main Thread ] start time = %lld \n", t1);
  ResumeThread(thread);
  WaitForSingleObject(thread, INFINITE);

  time_t t2 = time(NULL);
  printf("[ Main Thread ] sum = %lld \n", sum);
  printf("[ Main Thread ] end time = %lld \n", t2);
  printf("[ Main Thread ] time diff = %lld seconds \n", t2 - t1);
  CloseHandle(thread);

  return 0;
}