#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Matrix {
  private:
    int **matrix;
    int rows;
    int cols;
  public:
    Matrix(int rows, int cols): rows(rows), cols(cols) {
      matrix = new int*[rows];
      for(int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
      }
      fillRandom();
    }
    ~Matrix() {
      for(int i = 0; i < rows; i++) {
        delete [] matrix[i];
      }
      delete [] matrix;
    }
    void set(int row, int col, int value) {
      matrix[row][col] = value;
    }
    void fillRandom() {
      for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
          matrix[i][j] = rand() % 100;
        }
      }
    }
    int get(int row, int col) {
      return matrix[row][col];
    }
    void print() {
      for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
          cout << matrix[i][j] << " ";
        }
        cout << endl;
      }
    }
};

int main() {
  srand((unsigned) time(NULL));

  int rows, cols;
  cout << "행수와 열수 입력 (띄어쓰기로 구분): ";
  cin >> rows >> cols;

  Matrix *matrix = new Matrix(rows, cols);

  cout << endl;
  matrix->print();

  return 0;
}
