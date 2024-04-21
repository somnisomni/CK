#pragma once

class Bullet {
  private:
    int id;
  public:
    Bullet() { }
    ~Bullet() { }

    void setId(int id) { this->id = id; }
    int getId() const { return id; }
};
