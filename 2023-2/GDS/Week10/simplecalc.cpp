#include <iostream>
#include <cstring>
#include "./arraystack.h"
using namespace std;

enum TokenType { PLUS, MINUS, MULTI, DIVIDE, NUMBER, BLANK, END, INVALID = -1 };
const static char OP[] = { '+', '-', '*', '/' };

class SimpleCalculator {
  private:
    char* postfix;
    ArrayStack<double> stack;
    mutable double result;
    mutable int curReadPos;
  public:
    SimpleCalculator(int max = 100): stack(max), result(0.0), curReadPos(0) {
      postfix = new char[max];
    }
    ~SimpleCalculator() {
      if(postfix) delete [] postfix;
    }

    void setPostfix(const char* str) { strcpy(postfix, str); }
    TokenType getToken(char* token) const {
      int tokenPos = 0;
      switch(postfix[curReadPos]) {
        case '+':
          token[tokenPos++] = '+';
          token[tokenPos] = '\0';
          curReadPos++;
          return PLUS;
        case '-':
          token[tokenPos++] = '-';
          token[tokenPos] = '\0';
          curReadPos++;
          return MINUS;
        case '*':
          token[tokenPos++] = '*';
          token[tokenPos] = '\0';
          curReadPos++;
          return MULTI;
        case '/':
          token[tokenPos++] = '/';
          token[tokenPos] = '\0';
          curReadPos++;
          return DIVIDE;
        case ' ':
          curReadPos++;
          return BLANK;
        case '=': case '\0': return END;
        default:
          if(postfix[curReadPos] < '0' || postfix[curReadPos] > '9') return INVALID;

          while(postfix[curReadPos] >= '0' && postfix[curReadPos] <= '9')
            token[tokenPos++] = postfix[curReadPos++];
          token[tokenPos] = '\0';
          return NUMBER;
      }
    }
    void calculate() {
      double pop1, pop2;
      double number = 0;
      char token[50];

      curReadPos = 0;
      TokenType curType;
      while((curType = getToken(token)) != END) {
        switch(curType) {
          case PLUS:
            pop2 = stack.getTop(); stack.pop();
            pop1 = stack.getTop(); stack.pop();
            stack.push(pop1 + pop2);
            break;
          case MINUS:
            pop2 = stack.getTop(); stack.pop();
            pop1 = stack.getTop(); stack.pop();
            stack.push(pop1 - pop2);
            break;
          case MULTI:
            pop2 = stack.getTop(); stack.pop();
            pop1 = stack.getTop(); stack.pop();
            stack.push(pop1 * pop2);
            break;
          case DIVIDE:
            pop2 = stack.getTop(); stack.pop();
            pop1 = stack.getTop(); stack.pop();
            stack.push(pop1 / pop2);
            break;
          case BLANK: break;
          case NUMBER:
            number = 0;
            for(int i = 0; token[i] != '\0'; i++)
              number = number * 10 + (token[i] - '0');
            stack.push(number);
            break;
        }
      }
      result = stack.getTop();
    }
    double getResult() const { return result; }
    void print() {
      cout << "Postfix: " << postfix << " = " << result << endl;
    }
};

int main() {
  SimpleCalculator calc;

  char test[100] = "3 5 +";
  calc.setPostfix(test);
  calc.calculate();
  calc.print();

  return 0;
}
