#include <iostream>
#include <string>
using namespace std;

class StudentScore {
  private:
    int korean;
    int math;
  public:
    StudentScore(int korean, int math): korean(korean), math(math) { }
    int getKorean() { return korean; }
    int getMath() { return math; }
    int getSum() { return korean + math; }
    double getAverage() { return (korean + math) / 2.0; }
};

class Student {
  private:
    string name;
    int studentNum;
    StudentScore score;
  public:
    Student(string name, int studentNum, int korean, int math): name(name), studentNum(studentNum), score(korean, math) { }
    string getName() { return name; }
    int getStudentNum() { return studentNum; }
    StudentScore getScore() { return score; }
    void print() {
      cout << name << " (학번 " << studentNum << ") / 국어: " << score.getKorean() << ", 수학: " << score.getMath() << endl;
    }
};

void dumb_sort_print(Student students[], int size) {
  // 조잡한 O(n^2) 정렬 lol

  // 대상 데이터(총점) 주입
  int sums[size];
  int orders[size];
  for(int i = 0; i < size; i++) {
    sums[i] = students[i].getScore().getSum();
  }

  // 정렬
  for(int i = 0; i < size; i++) {
    int temp = -1;

    for(int j = 0; j < size; j++) {
      if(sums[j] > temp) {
        temp = sums[j];
        orders[i] = j;
      }
    }
    sums[orders[i]] = -1;
  }

  // 출력
  for(int i = 0; i < size; i++) {
    cout << students[orders[i]].getName() << " (학번 " << students[orders[i]].getStudentNum() << ") / ";
    cout << "총점: " << students[orders[i]].getScore().getSum() << ", 평균: " << students[orders[i]].getScore().getAverage() << endl;
  }
}

int main() {
  Student students[5] = {
    Student("아이유", 2014, 100, 80),
    Student("설현", 2015, 90, 97),
    Student("김수현", 2016, 79, 88),
    Student("장원영", 2017, 80, 100),
    Student("김동원", 2019, 93, 93)
  };

  for(Student student: students) {
    student.print();
  }
  cout << endl;
  dumb_sort_print(students, 5);

  return 0;
}
