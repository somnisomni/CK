#include <iostream>
#include <queue>
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

class BFS {
  private:
    queue<Node> bfsQueue;
    Node start;
    Node destination;
  public:
    BFS(Node start, Node dest): start(start), destination(dest) { }
    ~BFS() { }

    bool findPath() {
      VisitStatus visitInfo[SIZE];
      fill(visitInfo, visitInfo + SIZE, UNVISITED);

      bool found = false;

      bfsQueue.push(start);
      visitInfo[start] = VISITED;

      Node parent[SIZE];
      fill(parent, parent + SIZE, -1);
      parent[start] = start;

      while(!bfsQueue.empty()) {
        Node front = bfsQueue.front();
        bfsQueue.pop();
        if(front == destination) {
          found = true;
          break;
        }

        for(int i = 0; i < SIZE; i++) {
          if(GRAPH[front][i] && visitInfo[i] == UNVISITED) {
            bfsQueue.push(i);
            visitInfo[i] = VISITED;
            parent[i] = front;
          }
        }
      }

      return found;
    }

    void draw() {
      while(!bfsQueue.empty()) {
        int current = bfsQueue.front();
        cout << current << " <= ";
        bfsQueue.pop();
      }
    }
};


int main() {
  BFS bfs(0, 5);

  cout << bfs.findPath() << endl;
  bfs.draw();
}
