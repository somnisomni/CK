#include <cstdio>
#include <Windows.h>

class Point3D {
  private:
  int x;
  int y;
  int z;

  public:
  Point3D(int x, int y, int z): x(x), y(y), z(z) { }
  int getX() const { return x; }
  int getY() const { return y; }
  int getZ() const { return z; }
};

DWORD WINAPI ThreadCallback(LPVOID arg) {
  Sleep(1000);

  Point3D *pt = (Point3D *) arg;
  printf("Current Thread: %d / %d %d %d\n",  GetCurrentThreadId(),
    pt->getX(), pt->getY(), pt->getZ());
 
  return 0;
}

int main(int argc, char *argv[]) {
  for(int i = 0; i < 20; i++) {
    Point3D pt1(10, 20, 30);
    HANDLE thread1 = CreateThread(NULL, 0, ThreadCallback, &pt1, 0, NULL);
    if(thread1 == NULL) return 1;
    CloseHandle(thread1);

    Point3D pt2(40, 50, 60);
    HANDLE thread2 = CreateThread(NULL, 0, ThreadCallback, &pt2, 0, NULL);
    if(thread2 == NULL) return 1;
    CloseHandle(thread2);

    printf("Main Thread: %d\n", GetCurrentThreadId());
    Sleep(2000);
  }

  return 0;
}