#include <iostream>
#include <cstring>
using namespace std;

class Book {
  private:
    char *title;
    char *isbn;
    int price;
  public:
    Book(char *title, char *isbn, int price): price(price) {
      this->title = new char[strlen(title) + 1];
      this->isbn = new char[strlen(isbn) + 1];
      strcpy(this->title, title);
      strcpy(this->isbn, isbn);
    }
    Book(const Book& copy) {
      title = new char[strlen(copy.title) + 1];
      isbn = new char[strlen(copy.isbn) + 1];
      strcpy(title, copy.title);
      strcpy(isbn, copy.isbn);
      price = copy.price;
    }
    ~Book() {
      delete [] title;
      delete [] isbn;
    }
    void showBookInfo() const {
      cout << "제목: " << title << endl;
      cout << "ISBN: " << isbn << endl;
      cout << "가격: " << price << endl;
    }
    Book& operator=(const Book& ref) {
      delete [] title;
      delete [] isbn;
      title = new char[strlen(ref.title) + 1];
      isbn = new char[strlen(ref.isbn) + 1];
      strcpy(title, ref.title);
      strcpy(isbn, ref.isbn);
      price = ref.price;
      return *this;
    }
};

class EBook: public Book {
  private:
    char *drmKey;
  public:
    EBook(char *title, char *isbn, int price, char *drmKey): Book(title, isbn, price) {
      this->drmKey = new char[strlen(drmKey) + 1];
      strcpy(this->drmKey, drmKey);
    }
    EBook(const EBook& copy): Book(copy) {
      drmKey = new char[strlen(copy.drmKey) + 1];
      strcpy(drmKey, copy.drmKey);
    }
    ~EBook() {
      delete [] drmKey;
    }
    void showBookInfo() const {
      Book::showBookInfo();
      cout << "인증키: " << drmKey << endl;
    }
    EBook& operator=(const EBook& ref) {
      Book::operator=(ref);
      delete [] drmKey;
      drmKey = new char[strlen(ref.drmKey) + 1];
      strcpy(this->drmKey, ref.drmKey);
      return *this;
    }
};

int main() {
  EBook ebook1("C++ 프로그램 ebook", "555-12345-890-1", 10000, "fdx98dfx");
  EBook ebook2 = ebook1;
  ebook2.showBookInfo();
  cout << endl;
  EBook ebook3("dummy", "dummy", 0, "dummy");
  ebook3 = ebook2;
  ebook3.showBookInfo();

  return 0;
}
