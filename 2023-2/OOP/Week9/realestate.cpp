#include <iostream>
#include <string>
using namespace std;

class Building {
  protected:
    int pyeong;
    string address;
  public:
    Building(int p, string addr): pyeong(p), address(addr) { }
    ~Building() { }

    virtual void show() const {
      cout << "건물 평수: " << pyeong << endl;
      cout << "건물 주소: " << address << endl << endl;
    }
};

class House: public Building {
  protected:
    int numRooms;
    int cost;
  public:
    House(int p, string addr, int n, int c): Building(p, addr), numRooms(n), cost(c) { }
    ~House() { }

    virtual void show() const {
      cout << "집 평수: " << pyeong << endl;
      cout << "집 주소: " << address << endl;
      cout << "집 방 개수: " << numRooms << endl;
      cout << "집 가격: " << cost << endl << endl;
    }
};

class Office: public Building {
  protected:
    string zoneCode;
    int rent;
  public:
    Office(int p, string addr, string z, int r): Building(p, addr), zoneCode(z), rent(r) { }
    ~Office() { }

    virtual void show() const {
      cout << "사무실 평수: " << pyeong << endl;
      cout << "사무실 주소: " << address << endl;
      cout << "사무실 지역 코드: " << zoneCode << endl;
      cout << "사무실 임대료: " << rent << endl << endl;
    }
};

int main() {
  Building *buildings[3] = {
    new House(32, "경기도 부천시 원미구", 4, 350000000),
    new Office(24, "서울 종로구", "110-400", 250000000),
    new Office(24, "인천 서구", "405-222", 200000000)
  };

  for(int i = 0; i < 3; i++) buildings[i]->show();
  for(int i = 0; i < 3; i++) delete buildings[i];

  return 0;
}
