#include <iostream>
#include <string>
using namespace std;

struct Fish {
  string type;
  int weight;
  float length;
};

int main() {
  Fish fish;

  cout << "물고기 종류: ";
  cin >> fish.type;
  cout << "물고기 무게 (정수): ";
  cin >> fish.weight;
  cout << "물고기 길이: ";
  cin >> fish.length;

  cout << endl;
  cout << "물고기 종류: " << fish.type << endl;
  cout << "물고기 무게: " << fish.weight << endl;
  cout << "물고기 길이: " << fish.length << endl;
  cout << endl << endl;

  // =========

  Fish fishes[3] = {
    { "참치", 100, 2.5 },
    { "우럭", 50, 1.5 },
    { "연어", 70, 1.8 },
  };

  for(int i = 0; i < 3; i++) {
    cout << endl;
    cout << "물고기 종류: " << fishes[i].type << endl;
    cout << "물고기 무게: " << fishes[i].weight << endl;
    cout << "물고기 길이: " << fishes[i].length << endl;
  }

  return 0;
}
