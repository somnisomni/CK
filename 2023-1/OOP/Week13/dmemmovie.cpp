#include <iostream>
#include <string.h>
using namespace std;

struct Movie {
  char *title;
  float score;
};

char* dynStrInput() {
  char *str = new char[100];
  cin >> str;

  const int size = strlen(str) + 1;
  char *nStr = new char[size];
  strncpy(nStr, str, size);

  return nStr;
}

void inputMovies(Movie *movies, const int size) {
  for(int i = 0; i < size; i++) {
    cout << "영화 제목: ";
    movies[i].title = dynStrInput();
    cout << "영화 평점: ";
    cin >> movies[i].score;
    cout << endl;
  }
}

void printMovies(Movie *movies, const int size) {
  cout << "==============================" << endl;
  cout << " 제목\t평점" << endl;
  cout << "==============================" << endl;
  for(int i = 0; i < size; i++) {
    cout << " " << movies[i].title << "\t" << movies[i].score << endl;
  }
  cout << "==============================" << endl;
}

void freeMovieDynMembers(Movie *movies, const int size) {
  for(int i = 0; i < size; i++) {
    delete [] movies[i].title;
  }
}

int main() {
  int size = 0;
  cout << "몇 편이나 저장하시겠습니까?: ";
  cin >> size;

  Movie *movies = new Movie[size];

  inputMovies(movies, size);

  cout << endl;

  printMovies(movies, size);

  freeMovieDynMembers(movies, size);
  delete [] movies;
  return 0;
}
