#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct Point {
  int x, y;
};

void swapPoint(Point &p1, Point &p2) {
  Point temp = p1;
  p1 = p2;
  p2 = temp;
}

int main() {
  srand((unsigned) time(NULL));

  /* 구조체 배열에 랜덤 값 대입 및 출력 */
  Point ps[10];
  for(int i = 0; i < 10; i++) {
    ps[i] = { rand() % 100, rand() % 100 };
    cout << "ps[" << i << "] = (" << ps[i].x << ", " << ps[i].y << ")" << endl;
  }
  cout << endl;

  /* Bubble Sort 실행 */
  while(true) { // for(int j = 1; j < 9; j++)
    bool swapped = false;

    for(int i = 0; i < 9; i++) { // for(int i = 0; i < 10 - j; i++)
      if(ps[i].x > ps[i + 1].x) {
        swapPoint(ps[i], ps[i + 1]);
        swapped = true;
      }
    }

    if(!swapped) break;
  }

  /* 정렬 후 결과 출력 */
  cout << endl << "after sort" << endl;
  for(int i = 0; i < 10; i++) {
    cout << "ps[" << i << "] = (" << ps[i].x << ", " << ps[i].y << ")" << endl;
  }

  return 0;
}
