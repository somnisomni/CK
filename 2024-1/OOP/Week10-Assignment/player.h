#pragma once
#include <iostream>
#include "weapon.h"
using namespace std;

typedef unsigned int uint;

class PlayerBase {
  protected:
    IWeapon* equippedWeapon;

    PlayerBase(IWeapon* weapon): equippedWeapon(weapon) { }

  public:
    virtual ~PlayerBase() = default;
    virtual string getName() const = 0;
    virtual void move() {
      cout << getName() << " player moves" << endl;
    }
    virtual void attack() {
      if(equippedWeapon->fire()) {
        cout << getName() << " player attacks with " << getWeaponName() << endl;
      }
    }
    virtual void reload() {
      equippedWeapon->addAmmo(equippedWeapon->getMaxAmmo());
      cout << "Reloaded" << endl;
    }

    void changeWeapon(IWeapon* weapon) {
      equippedWeapon = weapon;
      cout << "Changed weapon to " << weapon->getWeaponName() << endl;
    }
    string getWeaponName() const {
      return equippedWeapon->getWeaponName();
    }
    uint getWeaponCurrentAmmo() const {
      return equippedWeapon->getCurrentAmmo();
    }
    uint getWeaponMaxAmmo() const {
      return equippedWeapon->getMaxAmmo();
    }
};

class Engineer: public PlayerBase {
  public:
    Engineer(IWeapon* weapon): PlayerBase(weapon) { }

    string getName() const override {
      return "Engineer";
    }
};

class Assault: public PlayerBase {
  public:
    Assault(IWeapon* weapon): PlayerBase(weapon) { }

    string getName() const override {
      return "Assault";
    }
};

class Medic: public PlayerBase {
  public:
    Medic(IWeapon* weapon): PlayerBase(weapon) { }

    string getName() const override {
      return "Medic";
    }
};
