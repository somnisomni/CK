#pragma once

class Item {
  private:
    int id;
    int count;

  public:
    Item(): id(-1), count(0) { }
    Item(int id, int count): id(id), count(count) { }

    int getId() const { return id; }
    int getCount() const { return count; }
};
