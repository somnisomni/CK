#include <iostream>
#include <cstring>
using namespace std;

class Student {
  private:
    char *id;
    char *name;
    int kor;
    int math;
  public:
    Student(char *id, char *name, int kor, int math) {
      this->id = new char[strlen(id) + 1];
      strcpy(this->id, id);
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
      this->kor = kor;
      this->math = math;
    }
    Student(const Student &copy) {
      id = new char[strlen(copy.id) + 1];
      strcpy(id, copy.id);
      name = new char[strlen(copy.name) + 1];
      strcpy(name, copy.name);
      kor = copy.kor;
      math = copy.math;
    }
    ~Student() {
      delete [] id;
      delete [] name;
      cout << "destruction" << endl;
    }
    void showData() const {
      cout << id << "\t" << name << "\t" << kor << "\t" << math << endl;
    }
};

int main() {
  char mid[10], mname[20];
  int mkor, mmath;

  cout << "id, name, kor, math >> ";
  cin >> mid >> mname >> mkor >> mmath;
  Student std1(mid, mname, mkor, mmath);
  Student std2 = std1;
  std1.showData();
  std2.showData();

  return 0;
}
