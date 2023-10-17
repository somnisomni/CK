#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class MyFriendInfo {
  private:
    char *name;
    ushort age;
  public:
    MyFriendInfo(char *name, const ushort age): age(age) {
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
    }
    ~MyFriendInfo() { delete [] name; }
    string getName() const { return name; }
    const ushort getAge() const { return age; }
};

class MyFriendDetailInfo: public MyFriendInfo {
  private:
    string addr;
    string phone;
  public:
    MyFriendDetailInfo(char *name, const ushort age, string addr, string phone): MyFriendInfo(name, age), addr(addr), phone(phone) { }
    ~MyFriendDetailInfo() { }
    string getAddr() const { return addr; }
    string getPhone() const { return phone; }
    void print() const {
      cout << "Name: " << getName() << endl;
      cout << "Age: "  << getAge()  << endl;
      cout << "Address: " << addr << endl;
      cout << "Phone: " << phone << endl;
    }
};

int main() {
  MyFriendDetailInfo f1("김국진", 24, "경기도 이천", "010-3423-3330");
  MyFriendDetailInfo f2("이수경", 22, "서울 서초구", "010-3539-9458");
  
  f1.print();
  cout << endl;
  f2.print();

  return 0;
}