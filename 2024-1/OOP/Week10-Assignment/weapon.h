#pragma once
#include <iostream>
using namespace std;

typedef unsigned int uint;

class IWeapon {
  public:
    virtual ~IWeapon() = default;
    virtual bool fire() = 0;
    virtual void addAmmo(const uint amount) = 0;
    virtual string getWeaponName() const = 0;
    virtual uint getCurrentAmmo() const = 0;
    virtual uint getMaxAmmo() const = 0;
};

class Gun: public IWeapon {
  private:
    const uint maxAmmo = 30;
    uint currentAmmo = maxAmmo;

  public:
    bool fire() override {
      if(currentAmmo <= 0) {
        cout << "Need reload!" << endl;
        return false;
      }

      cout << "Gun fires" << endl;
      currentAmmo--;
      return true;
    }

    void addAmmo(const uint amount) override {
      if(currentAmmo + amount > maxAmmo) {
        currentAmmo = maxAmmo;
        cout << "Extra " << amount - (maxAmmo - currentAmmo) << " ammo wasted" << endl;
      } else {
        currentAmmo += amount;
      }
    }

    string getWeaponName() const override {
      return "Gun";
    }

    uint getCurrentAmmo() const override {
      return currentAmmo;
    }

    uint getMaxAmmo() const override {
      return maxAmmo;
    }
};

class Rocket: public IWeapon {
  private:
    const uint maxAmmo = 5;
    uint currentAmmo = maxAmmo;

  public:
    bool fire() override {
      if(currentAmmo <= 0) {
        cout << "Need reload!" << endl;
        return false;
      }

      cout << "Rocket fires" << endl;
      currentAmmo--;
      return true;
    }

    void addAmmo(const uint amount) override {
      if(currentAmmo + amount > maxAmmo) {
        currentAmmo = maxAmmo;
        cout << "Extra " << amount - (maxAmmo - currentAmmo) << " ammo wasted" << endl;
      } else {
        currentAmmo += amount;
      }
    }

    string getWeaponName() const override {
      return "Rocket";
    }

    uint getCurrentAmmo() const override {
      return currentAmmo;
    }

    uint getMaxAmmo() const override {
      return maxAmmo;
    }
};

class Laser: public IWeapon {
  public:
    bool fire() override {
      cout << "Laser fires" << endl;
      return true;
    }

    void addAmmo(const uint amount) override {
      cout << "Laser does not need ammo, ignoring request" << endl;
    }

    string getWeaponName() const override {
      return "Laser";
    }

    uint getCurrentAmmo() const override {
      return 0;
    }

    uint getMaxAmmo() const override {
      return 0;
    }
};
