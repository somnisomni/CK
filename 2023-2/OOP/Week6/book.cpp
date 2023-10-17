#include <iostream>
#include <cstring>
using namespace std;

class Book {
  private:
    char *title;
    int price;
  public:
    Book(const char *title, int price): price(price) {
      this->title = new char[strlen(title) + 1];
      strcpy(this->title, title);
    }
    Book(const Book &copy) {
      title = new char[strlen(copy.title) + 1];
      strcpy(title, copy.title);
      price = copy.price;
    }
    ~Book() {
      delete [] title;
    }
    int getPrice() const {
      return price;
    }
};

int getPrice(Book obj) {
  return obj.getPrice();
}

int main() {
  Book b("C++", 11000);
  if(getPrice(b) >= 10000) {
    cout << "책을 사지 않겠습니다." << endl;
  } else {
    cout << "책을 사겠습니다." << endl;
  }
  return 0;
}
