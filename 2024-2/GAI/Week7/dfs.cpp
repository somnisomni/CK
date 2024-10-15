#include <iostream>
#include <stack>
using namespace std;

enum VisitStatus { UNVISITED = 0, VISITED = 1 };
typedef int Node;

const int SIZE = 9;
const Node GRAPH[SIZE][SIZE] = {
  { 0, 1, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 0 }
};

class DFS {
  private:
    stack<Node> dfsStack;
    Node start;
    Node destination;
  public:
    DFS(Node start, Node dest): start(start), destination(dest) { }
    ~DFS() { }

    bool findPath() {
      VisitStatus visitInfo[SIZE];
      fill(visitInfo, visitInfo + SIZE, UNVISITED);

      bool found = false;

      dfsStack.push(start);
      visitInfo[start] = VISITED;

      while(!dfsStack.empty() && !found) {
        bool visited = false;

        for(int i = 0; i < SIZE; i++) {
          if(GRAPH[dfsStack.top()][i] && visitInfo[i] == UNVISITED) {
            dfsStack.push(i);
            visitInfo[i] = VISITED;
            visited = true;
            break;
          }
        }

        if(visited == false) {
          dfsStack.pop();
        }

        if(dfsStack.top() == destination) {
          found = true;
        }
      }

      return found;
    }

    void draw() {
      while(!dfsStack.empty()) {
        int current = dfsStack.top();
        cout << current << " <= ";
        dfsStack.pop();
      }
    }
};

int main() {
  DFS dfs(0, 5);

  cout << dfs.findPath() << endl;
  dfs.draw();
}
