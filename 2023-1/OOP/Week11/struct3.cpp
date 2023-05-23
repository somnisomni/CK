#include <iostream>
#include <string>
using namespace std;

struct Member {
  string name;
  int age;
  float height;
  float weight;
};

int main() {
  Member member;

  cout << "이름: ";
  cin >> member.name;
  cout << "연령: ";
  cin >> member.age;
  cout << "신장: ";
  cin >> member.height;
  cout << "몸무게: ";
  cin >> member.weight;

  cout << endl;

  cout << "이름\t연령\t신장\t몸무게" << endl;
  cout << member.name << "\t" << member.age << "세\t" << member.height << "cm\t" << member.weight << "kg" << endl;

  return 0;
}
