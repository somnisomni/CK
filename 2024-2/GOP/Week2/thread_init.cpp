#include <thread>
#include <iostream>
using namespace std;

void thread_func() {
  cout << "Hello (thread_func)" << endl;

  for(int i = 0; i < 10; i++) {
    cout << "thread_func: " << i << endl;
  }
}

auto thread_lambda = []() {
  cout << "Hello (thread_lambda)" << endl;

  for(int i = 0; i < 10; i++) {
    cout << "thread_lambda: " << i << endl;
  }
};

int main() {
  thread t1(thread_func);
  thread t2(thread_lambda);
  thread t3([]() {
    cout << "Hello (anonymous lambda)" << endl;

    for(int i = 0; i < 10; i++) {
      cout << "anonymous lambda: " << i << endl;
    }
  });

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
