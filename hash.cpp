#include <iostream>
#include <cstring>
#include "node.h"
#include "student.cpp"
#include <cmath>

//create table and set size
const int initTableSize = 100;
Node** table;
int tableSize;
int hashFunc(int id);
int chainLen(Node* head);
void insertStudent(Student* s, Node** table);
void rehash(int tableSize);
void add(Node*& head, Node* cur, Node* prev, Node* newnext);
void print(Node* head, Node* cur);
void del(Node* &head, Node* prev, Node* cur, int id);
void sumgpa(Student* head, float &sum, int &count);

int main(){
  int running = 1;
  char fInput[20];
  char fNameInput[20];
  char lNameInput[20];
  int idInput;
  float gpaInput;
  char fNameData[20];
  char sNameData[20];
  int idData;
  float gpaData;
  int delInput;
  //Node* head = NULL;
  while (running == 1) {  
    cout << "what do you want" << endl;
    cin >> fInput;
    //add function, gets input and adds to node
    if (strcmp(fInput, "ADD")==0){
      Student* student1 = new Student;
      cout << "first name: " << endl;
      cin >> fNameInput;
      strcpy(student1->fname, fNameInput);
      //Node* fNameNode = new Node(student1);
      cout << "last name: " << endl;
      cin >> lNameInput;
      strcpy(student1->lname, lNameInput);
      cout << "id: " << endl;
      cin >> idInput;
      student1->id = idInput;
      cout << "gpa: " << endl;
      cin >> gpaInput;
      //rounding to 2 decmal places from chatgpt
      gpaInput = round(gpaInput * 100) / 100;
      student1->gpa = gpaInput;
      //add(head, head, head, fNameNode);
      insertStudent(student, table);
      cout << "added student" << endl;
      //print(head, head);
    }
    //print function
    else if (strcmp(fInput, "PRINT") ==0){
      for (int i = 0; i < tableSize; i++){
	print(table[i], table[i]);
	//print(head, head);
      }
    }
    //quit function
    else if (strcmp(fInput, "QUIT") ==0) {
      running = 0;
    }
    //delete function
    else if (strcmp(fInput, "DELETE") ==0) {
      cout << "what student do you want to delete" << endl;
      cin >> delInput;
      int index = hashFunc(delInput);
      if (tale[index] == nullptr) {
	cout << "this id does no exist" << endl;
      }
      else {
        del(table[index], table[index], table[index], id);
	cout << "student was deleted" << endl;
      }
    }
  }
  //make table
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
void insertStudent(Student* s, Node** targetTable) {
  int index = hashFunc(s->id);
  Node* newNode = new Node(s);
  newNode->setNext(table[index]);
  table[index] = newNode;
  int len = chainLen(table[index]);
  if (len > 3) {
    rehash(tableSize);
  }
}
void rehash() {
  //make new larger table
  Node** oldTable = table;
  int oldSize = tableSize;
  tableSize = tableSize * 2;
  int newSize = tableSize;
  Node** newTable = new Node*[newSize];
  Node* current = oldTable[i];
  for (int i = 0; i < oldSize; i++){
    Node* current = oldTable[i];
    while (current != nullptr) {
      insertStudent(current->getStudent(), newTable);
      current = current->getNext();
    }
  }
  table = newTable;
  //add nodes from old table to new table
  for (int i = 0; i < oldSize; i++) {
    Node* current = table[i];
    while (table[i] != nullptr){
      insertStudent(current->getStudent(), newTable);
      current = current->getNext();
    }
  }
}

//make current into the next
void add(Node*& head, Node* cur, Node* prev, Node* newnext){
  if(head == NULL){
    cout << head << endl;
    head = newnext;
    newnext->setNext(NULL);
  }
  else if (head->getStudent()->id > newnext->getStudent()->id){
    newnext->setNext(head);
    head = newnext;
  }
  else if(cur->getNext() == NULL){
    cout << "works" << endl;
    cur->setNext(newnext);
  }
  else if(cur->getStudent()->id > newnext->getStudent()->id){
    newnext->setNext(prev->getNext());
    prev->setNext(newnext);
  }
  else {
    add(head, cur->getNext(), cur, newnext);
  }
}

//print out next
void print(Node* head, Node* cur) {
  if(cur == head){
    cout << "student list: " << endl;
  }
  if(cur != NULL) {
    cout << cur->getStudent()->fname << " " << cur->getStudent()->lname << ", " << cur->getStudent()->id << ", " << cur->getStudent()->gpa << " " << endl;
    print(head, cur->getNext());
  }
  else {
    return;
  }
}

//delete node
void del(Node* &head, Node* prev, Node* cur, int id) {
  if (head->getStudent()->id == id) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  else if (cur->getStudent()->id == id){
    prev->next = cur->next;
    delete cur;
  }
  else {
    del(head, cur, cur->next, id);
  }
}

//help from chatgpt for getting average gpa
//finds sum of all gpas
void sumgpa(Node* head, float &sum, int &count){
  if (head == nullptr){
    return;
  }
  sum += head->getStudent()->gpa;
  count++;
  sumgpa(head->next, sum, count);
}
