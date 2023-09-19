#include <iostream>
#include <string>
using namespace std;

#define PI 3.141592f

class Circle {
  private:
    double radius;
    string name;
  public:
    Circle() { }
    void setCircle(const string name, const double radius) {
      this->name = name;
      this->radius = radius;
    }
    double getRadius() const { return radius; }
    string getName() const { return name; }
    double getArea() const { return radius * radius * PI; }
    void printInfo() const {
      cout << name << " (반지름: " << radius << ", 면적: " << getArea() << ")" << endl;
    }
};

class CircleManager {
  private:
    Circle *circles;
    unsigned int size;
  public:
    CircleManager(const unsigned int size): size(size) {
      this->circles = new Circle[size]();
    }
    ~CircleManager() { delete [] circles; }
    unsigned int getSize() const { return size; }
    Circle* getCircles() const { return circles; }
    void printAllCircles() const;
    void printCirclesAreaLargerThan(const double area) const;
};

void CircleManager::printAllCircles() const {
  cout << endl;
  cout << "== 모든 원 (개수: " << size << ") ==" << endl;
  for (int i = 0; i < size; i++) {
    circles[i].printInfo();
  }
  cout << endl;
}

void CircleManager::printCirclesAreaLargerThan(double area) const {
  cout << endl;
  cout << "== 면적이 " << area << "보다 큰 원 ==" << endl;
  for(int i = 0; i < size; i++) {
    if(circles[i].getArea() > area) {
      circles[i].printInfo();
    }
  }
  cout << endl;
}

CircleManager* createCircleManager() {
  unsigned int count;
  cout << "원의 개수: ";
  cin >> count;
  cout << endl;

  CircleManager *cm = new CircleManager(count);
  for (int i = 0; i < count; i++) {
    string name;
    double radius;

    cout << "[#" << i + 1 << "] 원 이름: ";
    cin >> name;
    cout << "[#" << i + 1 << "] 원 반지름: ";
    cin >> radius;
    cout << endl;

    cm->getCircles()[i].setCircle(name, radius);
  }

  return cm;
}

int main() {
  CircleManager *cm = createCircleManager();

  cout << endl;
  cm->printAllCircles();
  cm->printCirclesAreaLargerThan(10.0f);

  delete cm;
  return 0;
}
