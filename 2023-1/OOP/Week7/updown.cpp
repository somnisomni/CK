#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define IS_EQUAL 0
#define IS_GREATER 1
#define IS_LOWER 2

inline int createRandomNumber() { return rand() % 11; }

int diff(int target, int base) {
  if(target > base) {
    return IS_LOWER;
  } else if(target < base) {
    return IS_GREATER;
  } else {
    return IS_EQUAL;
  }
}

int tryGuess(int randNum) {
  int score = 0;

  for(int i = 0; i < 3; i++) {
    int input = 0;

    cout << "예상 숫자 입력: ";
    cin >> input;

    int diffres = diff(input, randNum);
    if(diffres == IS_LOWER) {
      cout << "더 작은 숫자입니다." << endl;
    } else if(diffres == IS_GREATER) {
      cout << "더 큰 숫자입니다." << endl;
    } else if(diffres == IS_EQUAL) {
      cout << "정답입니다." << endl;

      score = 100 - (i * 10);
      break;
    }
  }

  return score;
}

int main() {
  srand((unsigned) time(NULL));

  char restart = 'y';
  while(restart == 'y') {
    int num = createRandomNumber();
    cout << "랜덤 숫자 선택 완료 (0 ~ 10)" << endl;

    int score = tryGuess(num);
    if(score == 0) {
      cout << "랜덤 숫자는 " << num << " 입니다." << endl;
    }

    cout << "게임 종료, 점수: " << score << endl;
    cout << "게임 다시 시작? (y/n) ";
    cin >> restart;

    cout << endl;
  }

  return 0;
}
