#include <chrono>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::chrono;

class Timer {
  private:
    const int timerNo;
    time_point<high_resolution_clock> startTime;

  public:
    Timer(const int timerNo): timerNo(timerNo) {
      startTime = high_resolution_clock::now();
    }

    ~Timer() {
      stop();
    }

    long long stop() {
      auto end = high_resolution_clock::now();

      auto start = time_point_cast<milliseconds>(startTime).time_since_epoch().count();
      auto stop = time_point_cast<milliseconds>(end).time_since_epoch().count();

      auto duration = stop - start;

      cout << "timer" << timerNo << ": " << duration << "msec" << endl;
      return duration;
    }
};

int main(int argc, const char* argv[]) {
  int threadCount = 0;

  if(argc == 2) {
    threadCount = atoi(argv[1]);
  } else {
    cout << "Enter the number of threads: ";
    cin >> threadCount;
  }

  std::vector<std::thread> threadVector;
  const int TEST_COUNT = 1000000000;

  auto work = [](int threadNo, int testCount) {
    Timer timer(threadNo);

    int anotherCount = testCount;

    for(int i = 0; i <= testCount; i++) {
      anotherCount *= 2;
      anotherCount /= 2;
      anotherCount++;
      anotherCount--;

      if(i % (TEST_COUNT / 10) == 0
        || i == testCount) {
        cout << "thread" << threadNo << ": " << i << endl;
      }
    }
  };

  for(int i = 0; i < threadCount; ++i) {
    thread th(work, i, TEST_COUNT / threadCount);
    threadVector.push_back(std::move(th));
  }

  for(int i = 0; i < threadCount; ++i) {
    cout << "thread" << i << ": join()" << endl;
    threadVector[i].join();
  }

  return 0;
}
