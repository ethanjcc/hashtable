#include "student.cpp"
#ifndef NODE_H
#define NODE_H

class Node{
  public:
    // Pointer to student object
    Student* value;
    // Pointer to next node
    Node* next;
    // Constructor
    Node(Student* initStudPtr);
    // Deconstructor
    // NOTE: in order to prevent memory leaks, deleting a node will delete the next node in the list, which will then continue down the list, make sure to use setNext(nullptr) before deleting and ensure that the next node is pointed to somewhere else
    ~Node();
    // Get pointer to next node
    Node* getNext();
    // Get pointer to the student object
    Student* getStudent();
    // Set pointer to next node
    void setNext(Node* nextNode);
};

#endif
