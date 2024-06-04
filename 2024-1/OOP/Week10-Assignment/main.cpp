#include <iostream>
#include "player.h"
#include "weapon.h"
using namespace std;

char showMenu(const PlayerBase& player) {
  cout << endl;
  cout << " *** FPS GAME ?! ***" << endl;
  cout << "  You are playing as < " << player.getName() << " >" << endl;
  cout << "  Your weapon is < " << player.getWeaponName() << " > (" << player.getWeaponCurrentAmmo() << " / " << player.getWeaponMaxAmmo() << ")" << endl;
  cout << endl;
  cout << " 1. Move" << endl;
  cout << " 2. Attack" << endl;
  cout << " 3. Reload" << endl;
  cout << endl;
  cout << " e. Change player to Engineer" << endl;
  cout << " a. Change player to Assault" << endl;
  cout << " m. Change player to Medic" << endl;
  cout << endl;
  cout << " g. Change weapon to Gun" << endl;
  cout << " r. Change weapon to Rocket" << endl;
  cout << " l. Change weapon to Laser" << endl;
  cout << endl;
  cout << " q. Quit" << endl;
  cout << endl;
  cout << "  Your input >> ";

  char input;
  cin >> input;
  return input;
}

int main() {
  // Var init
  IWeapon *weapon = new Gun();
  PlayerBase *player = new Engineer(weapon);

  // Loop
  char lastInput = 0;
  while(lastInput != 'q') {
    system("cls");
    lastInput = showMenu(*player);
    cout << endl;

    if(lastInput == 'q') break;

    bool isInputValid = true;
    switch(lastInput) {
      case '1': player->move(); break;
      case '2': player->attack(); break;
      case '3': player->reload(); break;

      case 'e':
        delete player;
        player = new Engineer(weapon);
        cout << "Switched to " << player->getName() << endl;
        break;
      case 'a':
        delete player;
        player = new Assault(weapon);
        cout << "Switched to " << player->getName() << endl;
        break;
      case 'm':
        delete player;
        player = new Medic(weapon);
        cout << "Switched to " << player->getName() << endl;
        break;

      case 'g':
        delete weapon;
        weapon = new Gun();
        player->changeWeapon(weapon);
        break;
      case 'r':
        delete weapon;
        weapon = new Rocket();
        player->changeWeapon(weapon);
        break;
      case 'l':
        delete weapon;
        weapon = new Laser();
        player->changeWeapon(weapon);
        break;

      default:
        isInputValid = false;
        break;
    }

    if(isInputValid) {
      cout << endl;
      system("pause");
    }
  }

  // Exit
  if(player != nullptr) delete player;
  if(weapon != nullptr) delete weapon;
  return 0;
}
