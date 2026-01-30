#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//makes struct for student

struct Student {
  public:
   char* fname = new char[20];
   char* lname = new char[20];
   int id;
   float gpa;
};
#endif
