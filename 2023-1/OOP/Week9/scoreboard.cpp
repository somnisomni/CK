#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define STUDENT_LENGTH 5

int main() {
  srand((unsigned) time(NULL));

  int scores[STUDENT_LENGTH][3];
  int sums[4] = { 0, };

  for(int y = 0; y < STUDENT_LENGTH; y++) {
    for(int x = 0; x < 3; x++) {
      scores[y][x] = rand() % 101; // 0 ~ 100
    }
  }

  cout << "학번\t국어\t영어\t수학\t총점" << endl;
  for(int i = 0; i < STUDENT_LENGTH; i++) {
    cout << (i + 1) << "\t" << scores[i][0] << "\t" << scores[i][1] << "\t" << scores[i][2] << "\t";
    cout << scores[i][0] + scores[i][1] + scores[i][2] << endl;

    sums[0] += scores[i][0];
    sums[1] += scores[i][1];
    sums[2] += scores[i][2];
    sums[3] += scores[i][0] + scores[i][1] + scores[i][2];
  }

  cout << "총점\t" << sums[0] << "\t" << sums[1] << "\t" << sums[2] << "\t" << sums[3] << endl;

  return 0;
}
