#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> testVector;
  const int* vectorPointer = nullptr;

  int reserveSize;
  cout << "Enter reserve size: ";
  cin >> reserveSize;

  testVector.reserve(reserveSize);

  while(true) {
    // push_back 한 후 벡터의 메모리 주소 산출
    const int* newVectorPointer = &(testVector[0]);

    // push_back 이전과 메모리 주소 비교
    const bool pointerChanged = vectorPointer != newVectorPointer;

    // 비교를 위해 새로운 주소 저장
    vectorPointer = newVectorPointer;

    // 메모리 주소가 변경되는 경우 마킹
    cout << "vectorSize: " << testVector.size() << " vectorPointer: " << vectorPointer << (pointerChanged ? " (changed)" : "") << endl;

    // * === * //
    int input;
    cout << "Enter count (0: exit): ";
    cin >> input;

    // 0을 입력하면 종료
    if(input == 0) break;

    // 입력받은 개수만큼 벡터에 추가
    for(int i = 0; i < input; i++)
      testVector.push_back(input);
  }
}
