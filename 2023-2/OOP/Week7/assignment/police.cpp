#include <iostream>
using namespace std;

class Gun {
  private:
    int bulletCount;
  public:
    Gun(int bullet = 30): bulletCount(bullet) { }
    void shot() {
      if(bulletCount > 0) {
        cout << "빵야!" << endl;
        bulletCount--;
      } else {
        cout << "남아있는 총알이 없습니다." << endl;
      }
    }
    void show() const {
      cout << "총알 개수: " << bulletCount << endl;
    }
};

class Police {
  private:
    int handcuffs;
    Gun *pistol;
  public:
    Police(int bulletCount, int cuffCount): handcuffs(cuffCount) {
      if(bulletCount > 0) pistol = new Gun(bulletCount);
      else pistol = NULL;
    }
    ~Police() {
      delete pistol;
    }
    void shot() {
      if(pistol != NULL) {
        pistol->shot();
      } else {
        cout << "권총을 가지고 있지 않습니다." << endl;
      }
    }
    void putHandcuff() {
      if(handcuffs > 0) {
        cout << "철컹!" << endl;
        handcuffs -= 1;
      } else {
        cout << "수갑을 가지고 있지 않습니다." << endl;
      }
    }
    void showHandcuff() const {
      cout << "수갑 개수: " << handcuffs << endl;
    }
    void showAll() const {
      cout << "=== 경찰 ===" << endl;

      if(pistol != NULL) {
        pistol->show();
      } else {
        cout << "권총 미보유" << endl;
      }
      showHandcuff();
    }
};

int main() {
  Police pMan1(5, 2);
  pMan1.shot();
  pMan1.putHandcuff();
  pMan1.showHandcuff();

  cout << endl;

  Police pMan2(0, 1);
  pMan2.shot();
  pMan2.putHandcuff();
  pMan2.showHandcuff();

  cout << endl << endl;
  
  pMan1.showAll();
  cout << endl;
  pMan2.showAll();

  return 0;
}