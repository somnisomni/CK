#include <iostream>
#include <memory>
using namespace std;

class Player {
  private:
    int id;
  public:
    Player(int id): id(id) {
      cout << "Player #" << id << " created" << endl;
    }
    ~Player() {
      cout << "Player #" << id << " destroyed" << endl;
    }
    int getId() const {
      return id;
    }
};

int main() {
  shared_ptr<Player> playerPtr1 = make_shared<Player>(1);
  shared_ptr<Player> playerPtr2 = make_shared<Player>(2);
  shared_ptr<Player> playerPtr3 = make_shared<Player>(3);
  cout << "playerPtr1.use_count(): " << playerPtr1.use_count() << endl;  // 1
  cout << "playerPtr2.use_count(): " << playerPtr2.use_count() << endl;  // 1
  cout << "playerPtr3.use_count(): " << playerPtr3.use_count() << endl;  // 1
  cout << endl;

  playerPtr1 = playerPtr3;
  playerPtr2 = playerPtr2;
  cout << "playerPtr1.use_count(): " << playerPtr1.use_count() << endl; // 2
  cout << "playerPtr2.use_count(): " << playerPtr2.use_count() << endl; // 1
  cout << "playerPtr3.use_count(): " << playerPtr3.use_count() << endl; // 2

  return 0;
}
