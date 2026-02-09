#include <iostream>
#include <cstring>
#include "node.h"
#include "student.cpp"

//create table and set size
const int initTableSize = 100;
Node** table;
int tableSize;
int hashFunc(int id);
int chainLen(Node* head);
void insertStudent(Student* s, Node** table);
void rehash(int tableSize);

int main(){
  tableSize = initTableSize;
  table = new Node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
}

//hash function from copilot
int hashFunc(int id) {
  return id % tableSize;
}
//create length of chain
int chainLen(Node* head) {
  int len = 0;
  Node* cur = head;
  //add to length when a node is added
  while (cur != nullptr) {
    len++;
    cur = cur->getNext();
  }
  return len;
}
//put student into the table
void insertStudent(Student* s, Node** table) {
  int index = hashFunc(s->id);
  Node* newNode = new Node(s);
  newNode->setNext(table[index]);
  table[index] = newNode;
  int len = chainLen(table[index]);
  if (len > 3) {
    rehash(tableSize);
  }
}
void rehash(int tableSize) {
  //make new larger table
  int oldSize = tableSize;
  int newSize = oldSize * 2;
  Node** newTable = new Node*[newSize];
  for (int i = 0; i < newSize; i++) {
    newTable[i] = nullptr;
  }
  //add nodes from old table to new table
  for (int i = 0; i < oldSize; i++) {
    while (table[i] != nullptr){
      insertStudent(table[i]->getStudent(), newTable);
      table[i] = table[i]->getNext();
    }
  }
}

