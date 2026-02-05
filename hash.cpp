#include <iostream>
#include <cstring>

//create table and set size
const int initTableSize = 100;
Node** table;
int tableSize;

int main(){
  tableSize = initTableSize;
  table = new Node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
  //hash function from copilot
  int hashFunc(int id, int tableSize) {
    return id % tableSize;
  }
  //create length of chain
  int chainLen(Node* head) {
    int len = 0;
    Node* cur = head;
    //add to length when a node is added
    while (cur != nullptr) {
      len++;
      cur = cur->getNext;
    }
  }
  //put student into the table
  void insertStudent(Student* s) {
    int index = hashFunc(s->id);
    Node* newNode = new Node(s);
    newNode->setNext(table[index]);
    table[index] = newNode;
    int len = chainLen(table[index]);
    if (len > 3) {
      rehash;
    }
  }
}
