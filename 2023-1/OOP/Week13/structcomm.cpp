#include <iostream>
using namespace std;

typedef struct {
  char name[10];
  char mail[50];
  int mobile;
} PROFESSOR;

typedef struct {
  char name[10];
  char major[20];
  int id;
  float score;
} STUDENT;

typedef struct {
  char type;  // "P": 교수, "S": 학생
  union {
    PROFESSOR prof;
    STUDENT stu;
  } u;
} PERSON;
