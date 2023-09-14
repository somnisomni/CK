#pragma once
#include <iostream>
#include <string>
using namespace std;

enum CardShape {
  SPADE,
  HEART,
  DIAMOND,
  CLUB
};

string getCardShapeName(CardShape shape) {
  switch (shape) {
    case SPADE:
      return "스페이드";
    case HEART:
      return "하트";
    case DIAMOND:
      return "다이아몬드";
    case CLUB:
      return "클럽";
    default:
      return "알 수 없음";
  }
}

class Card {
  private:
    CardShape shape;
    char character;
    bool faceUp = false;
  public:
    Card(CardShape _shape, char _char, bool _faceUp = false): shape(_shape), character(_char), faceUp(_faceUp) { }
    ~Card() { }

    void flip() { faceUp = !faceUp; }
    bool isFaceUp() { return faceUp; }
    CardShape getShape() { return shape; }
    char getCharacter() { return character; }
    void draw();
};

void Card::draw() {
  if(isFaceUp()) {
    cout << "모양: " << getCardShapeName(shape) << endl;
    cout << "값: " << character << endl;
  } else {
    cout << "카드가 뒤집혀 있습니다." << endl;
  }
}
