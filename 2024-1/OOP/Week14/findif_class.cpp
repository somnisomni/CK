#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class PlayerData {
  public:
    string playerName;

  public:
    PlayerData(std::string strName) : playerName(strName) {
      std::cout << "생성자 " << std::endl;
    }
    PlayerData(PlayerData &data) : playerName(data.playerName) {
      std::cout << "복사 생성자 " << std::endl;
    }
    PlayerData(PlayerData &&data) noexcept : playerName(move(data.playerName)) {
      std::cout << "이동 생성자 " << std::endl;
    }
    ~PlayerData() {
      std::cout << "소멸자 " << std::endl;
    }
};

bool checkLength(const PlayerData &pData) {
  return pData.playerName.length() > 3;
}

int main() {
  vector<PlayerData> players;
  players.emplace_back("Cat");
  players.emplace_back("Dog");
  players.emplace_back("Mouse");
  players.emplace_back("Cow");

  auto beginIterator = cbegin(players);
  auto endIterator = cend(players);

  auto findIterator = find_if(beginIterator, endIterator, checkLength);
  if(findIterator == endIterator) {
    cout << "not found" << endl;
  } else {
    cout << "found player : " << findIterator->playerName << endl;
  }

  return 0;
}
