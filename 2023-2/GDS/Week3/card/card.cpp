#include <iostream>
#include "./card.h"
using namespace std;

int main() {
  Card spade7(SPADE, '7');
  spade7.flip();
  spade7.draw();

  return 0;
}
