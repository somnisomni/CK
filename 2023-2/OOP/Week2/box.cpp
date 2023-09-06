#include <iostream>
using namespace std;

class Box {
  private:
    int width;
    int height;
    int length;
  public:
    bool init(int w, int h, int l);
    int calVolume();
};

bool Box::init(int w, int h, int l) {
  if(w <= 0 || h <= 0 || l <= 0) {
    return false;
  }

  width = w;
  height = h;
  length = l;
  return true;
}

int Box::calVolume() {
  return width * height * length;
}

bool initBox(Box *box) {
  int w, h, l;

  cout << "가로: ";
  cin >> w;
  cout << "세로: ";
  cin >> h;
  cout << "높이: ";
  cin >> l;
  cout << endl;

  if(!box->init(w, h, l)) {
    cout << "박스의 각 변은 0보다 커야합니다." << endl;
    return false;
  }
  return true;
}

int main() {
  Box box;
  if(initBox(&box)) {
    cout << "계산된 부피: " << box.calVolume() << endl;
  }

  return 0;
}
