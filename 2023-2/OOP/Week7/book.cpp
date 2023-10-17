#include <iostream>
#include <cstring>
using namespace std;

class Book {
  protected:
    char *title;
    char *isbn;
    int price;
  public:
    Book(const char *title, const char *isbn, const int price): price(price) {
      this->title = new char[strlen(title) + 1];
      strcpy(this->title, title);

      this->isbn = new char[strlen(isbn) + 1];
      strcpy(this->isbn, isbn);
    }
    ~Book() {
      delete [] title;
      delete [] isbn;
    }
    void showInfo() const {
      cout << "제목: " << title << endl;
      cout << "ISBN: " << isbn << endl;
      cout << "가격: " << price << endl;
    }
};

class EBook: protected Book {
  private:
    char *drmKey;
  public:
    EBook(const char *title, const char *isbn, const int price, const char *drmKey): Book(title, isbn, price) {
      this->drmKey = new char[strlen(drmKey) + 1];
      strcpy(this->drmKey, drmKey);
    }
    ~EBook() {
      delete [] drmKey;
    }
    void showInfo() const {
      Book::showInfo();
      // cout << "제목: " << title << endl;
      // cout << "ISBN: " << isbn << endl;
      // cout << "가격: " << price << endl;
      cout << "인증키: " << drmKey << endl;
    }
};

int main() {
  Book book("C++ 프로그램", "555-12345-890-0", 20000);
  book.showInfo();
  cout << endl;

  EBook ebook("C++ 프로그램 e-Book", "555-12345-890-1", 10000, "fdx98dfx");
  ebook.showInfo();

  return 0;
}