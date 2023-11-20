#include <iostream>
#include "./arraystack.h"
using namespace std;

int main() {
  ArrayStack<int> intStack(10);
  ArrayStack<float> floatStack(5);
  for(int i = 0; i < 5; i++) intStack.push(i * 10);
  for(int i = 0; i < 5; i++) floatStack.push(i * 2.3f);

  cout << "int Top: " << intStack.getTop() << endl;
  cout << "float Top: " << floatStack.getTop() << endl;

  intStack.pop();
  cout << "int Top: " << intStack.getTop() << endl;
  floatStack.pop();
  cout << "float Top: " << floatStack.getTop() << endl;

  intStack.push(1000);
  while(!intStack.isEmpty()) {
    cout << "int Top: " << intStack.getTop() << endl;
    intStack.pop();
  }

  floatStack.push(34.56f);
  while(!floatStack.isEmpty()) {
    cout << "float Top: " << floatStack.getTop() << endl;
    floatStack.pop();
  }

  return 0;
}
