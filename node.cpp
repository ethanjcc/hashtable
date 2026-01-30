#include "Node.h"

Node::Node(Student* initStudPtr) {
  value = initStudPtr;
  next = nullptr;
}

Node::~Node() {
  delete value;
}

Node* Node::getNext() { return next; }
Student* Node::getStudent() { return value; }
void Node::setNext(Node* newnext) { next = newnext; }
