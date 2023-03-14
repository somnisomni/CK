// 강의 듣다가 심심해서 만든 XOR Encrypt (C++ 버전)

#include <iostream>
#include <list>
using namespace std;

list<unsigned short> xorEncrypt(string message, string key) {
  unsigned long msgsize = message.size();
  unsigned long keysize = key.size();
  list<unsigned short> encrypted = { };

  for(unsigned long i = 0; i < msgsize; i++) {
    encrypted.push_back((unsigned short) (message[i] ^ key[i % keysize]));
  }

  return encrypted;
}

int main() {
  list<unsigned short> enc = xorEncrypt("TEST MESSAGE", "helloworld");
  for(unsigned short encitem : enc) {
    cout << "0x" << hex << encitem << " ";
  }
  cout << endl;

  return 0;
}
