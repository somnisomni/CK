#include <iostream>
#include <string>
using namespace std;

enum Genre {
  BALLAD,
  HIPHOP,
  DANCE,
  SOUL,
  JAZZ
};

struct Song {
  string title;
  string artist;
  Genre genre;
};

string genreStr(Genre genre) {
  switch(genre) {
    case BALLAD:
      return "발라드";
    case HIPHOP:
      return "힙합";
    case DANCE:
      return "댄스";
    case SOUL:
      return "소울";
    case JAZZ:
      return "재즈";
  }
  return "알 수 없음";
}

int main() {
  Song songs[3] = {
    { "밤편지", "아이유", BALLAD },
    { "서울밤", "어반자카파", SOUL },
    { "썸머", "GRAY", SOUL }
  };

  cout << "제   목\t\t아 티 스 트\t\t장    르" << endl;
  for(int i = 0; i < 3; i++) {
    cout << songs[i].title << "\t\t" << songs[i].artist << "\t\t" << genreStr(songs[i].genre) << endl;
  }

  return 0;
}
