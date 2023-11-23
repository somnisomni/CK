#include "../Week10/arraystack.h"
#include <iostream>
using namespace std;

static const char NODENAME[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
static const int NODES[9][9] = {
  /* A ~ I */
  {0, 1, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 1, 0}
};

class DFS {
  private:
    ArrayStack<int> stack;
    int start;
    int target;
    bool found;
  public:
    DFS(int s, int t): stack(100), start(s), target(t), found(false) { }
    ~DFS() { }

    void findPath() {
      bool visited[9];
      for(int i = 0; i < 9; i++) visited[i] = false;

      stack.push(start);
      visited[start] = true;

      while(!stack.isEmpty() && target != stack.getTop()) {
        int curNode = stack.getTop();
        bool visitNext = false;
        for(int next = 0; next < 9; next++) {
          if(NODES[curNode][next] == 1 && visited[next] == false) {
            stack.push(next);
            visited[next] = true;
            visitNext = true;
            break;
          }
        }

        if(visitNext == false) stack.pop();
      }
    }

    void print() {
      ArrayStack<int> path(stack.getMax());
      while(!stack.isEmpty()) {
        path.push(stack.getTop());
        stack.pop();
      }

      while(!path.isEmpty()) {
        int node = path.getTop();
        path.pop();
        cout << NODENAME[node] << " -> ";
      }
      cout << "[finish]" << endl;
    }
};

int main() {
  DFS dfs(0, 5);
  dfs.findPath();
  dfs.print();
  return 0;
}
