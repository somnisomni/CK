#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class ObjectManager {
  private:
    vector<T> objects;
  public:
    void addObject(const T& entity) {
      objects.push_back(entity);
      cout << "push" << endl;
    }
    const T& getObject(int index) {
      cout << "get" << endl;
      return objects.at(index);
    }
};

void exampleOne() {
  ObjectManager<int> intObjectMgr;
  ObjectManager<string> stringObjectMgr;

  intObjectMgr.addObject(10);
  stringObjectMgr.addObject("가나다");

  auto intVal = intObjectMgr.getObject(0);
  auto stringVal = stringObjectMgr.getObject(0);

  cout << intVal << endl;
  cout << stringVal << endl;
}

void exampleTwo() {
  using objController = ObjectManager<int>;
  ObjectManager<int> arrMgr[3];
  objController arrCtrlr[3];

  ObjectManager<int*> ptrArrMgr[10];
  ObjectManager<ObjectManager<int>> dObjMgr;

  dObjMgr.addObject(arrMgr[0]);
  dObjMgr.addObject(arrMgr[1]);
  dObjMgr.addObject(arrMgr[2]);

  auto entityObjMgr = dObjMgr.getObject(0);
  entityObjMgr.addObject(100);
  auto entity = entityObjMgr.getObject(0);
  cout << "entity val: " << entity << endl;
}

int main()
{
  exampleTwo();
}
