#include <iostream>
#include <cstring>
using namespace std;

class MyString {
  private:
    char *str;
    int len;
  public:
    MyString(): str(NULL), len(0) { }
    MyString(const char *str) {
      len = strlen(str);
      this->str = new char[len + 1];
      strcpy(this->str, str);
    }
    ~MyString() {
      delete [] str;
    }

    int length() const { return len; }

    MyString operator+(const MyString &s) {
      MyString tmp;
      tmp.len = len + s.len;
      tmp.str = new char[tmp.len + 1];
      strcpy(tmp.str, str);
      strcat(tmp.str, s.str);

      return tmp;
    }
    char operator[](int index) {
      if(index < 0 || index > len - 1) {
        cout << "Out of index" << endl;
        exit(1);
      }

      return str[index];
    }
    MyString& operator=(const MyString &s) {
      if(this == &s)
        return *this;

      delete [] str;
      len = s.len;
      str = new char[len + 1];
      strcpy(str, s.str);

      return *this;
    }
    friend ostream& operator<<(ostream &out, const MyString &s);
    friend istream& operator>>(istream &in, MyString &s);
    friend bool operator==(const MyString &s1, const MyString &s2);
    friend bool operator!=(const MyString &s1, const MyString &s2);
};

ostream& operator<<(ostream &out, const MyString &s) {
  out << s.str;
  return out;
}

istream& operator>>(istream &in, MyString &s) {
  char tmp[100];
  in >> tmp;
  s = MyString(tmp);
  return in;
}

bool operator==(const MyString &s1, const MyString &s2) {
  return strcmp(s1.str, s2.str) == 0;
}

bool operator!=(const MyString &s1, const MyString &s2) {
  return strcmp(s1.str, s2.str) != 0;
}

int main() {
  MyString str1("hello");
  MyString str2("my world");
  MyString str3;

  if(str1 == str2) cout << "str1 == str2" << endl;
  else cout << "str1 != str2" << endl;

  cin >> str3;
  cout << str3 << endl;;

  MyString str4 = str1 + str2;
  cout << str4 << endl;
  cout << str4[3] << endl;
}
