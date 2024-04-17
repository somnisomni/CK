#include <iostream>
#include <memory>
using namespace std;

class Player {
  private:
    unique_ptr<int> haveWeaponId;

  public:
    Player(): haveWeaponId(nullptr) {
      haveWeaponId = make_unique<int>(10);
      cout << "Player created and weapon assigned" << endl;
    }
    ~Player() {
      cout << "Player destroyed" << endl;
    }

    int getWeaponId() const {
      return *haveWeaponId;
    }
};

int main() {
  unique_ptr<int> p1(new int(5));
  cout << "&p1: " << &(*p1) << endl;

  unique_ptr<int> p2 = move(p1);
  cout << "&p1: " << &(*p1) << endl;
  cout << "&p2: " << &(*p2) << endl;

  // //

  Player player;
  cout << "weapon id: " << player.getWeaponId() << endl;

  // //

  unique_ptr<Player> playerPtr = make_unique<Player>();
  unique_ptr<Player> playerPtr2(new Player());
  cout << "playerPtr.get() " << playerPtr.get() << endl;
  cout << "playerPtr2.get() " << playerPtr2.get() << endl;

  Player* playerRel = playerPtr.release();
  cout << "&(*playerRel): " << &(*playerRel) << endl;
  delete playerRel;

  return 0;
}
