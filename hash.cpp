#include <iostream>
#include <cstring>
#include "node.h"
#include "student.cpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

//create table and set size
const int initTableSize = 100;
Node** table;
int tableSize;
int nextId = 1;
int hashFunc(int id);
int chainLen(Node* head);
void insertStudent(Student* s, Node** table);
void rehash();
void add(Node*& head, Node* cur, Node* prev, Node* newnext);
void print(Node* head, Node* cur);
void del(Node* &head, Node* prev, Node* cur, int id);
void sumgpa(Student* head, float &sum, int &count);
void gen(int count);

int main() {
  srand(time(NULL));
  //make table
  tableSize = initTableSize;
  table = new Node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
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
      insertStudent(student1, table);
      cout << "added student" << endl;
      //print(head, head);
    }
    //print function
    else if (strcmp(fInput, "PRINT") ==0){
      cout << "student list: " << endl;
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
      if (table[index] == nullptr) {
	cout << "this id does no exist" << endl;
      }
      else {
        del(table[index], table[index], table[index]->getNext(), delInput);
	cout << "student was deleted" << endl;
      }
    }
    else if (strcmp(fInput, "GEN") == 0) {
      int count;
      cin >> count;
      gen(count);
    }
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
  newNode->setNext(targetTable[index]);
  targetTable[index] = newNode;
  int len = chainLen(targetTable[index]);
  if (len > 3) {
    rehash();
  }
}
void rehash() {
  //make new larger table
  Node** oldTable = table;
  int oldSize = tableSize;
  tableSize = tableSize * 2;
  int newSize = tableSize;
  Node** newTable = new Node*[newSize];
  for (int i = 0; i < newSize; i++) {
    newTable[i] = nullptr;
  }
  //add nodes from old table to new table
  for (int i = 0; i < oldSize; i++) {
    Node* current = oldTable[i];
    while (current != nullptr){
      insertStudent(current->getStudent(), newTable);
      current = current->getNext();
    }
  }
  table = newTable;
  delete[] oldTable;
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

void gen(int count){
  //copilot helped with getting random student
  //get first names
  vector<string> firstName;
  ifstream ffile("firstname.txt");
  string fname;

  while (getline(ffile, fname)) {
    if (!fname.empty()) {
      firstName.push_back(fname);
    }
  }
  ffile.close();

  //get last names
  vector<string> lastName;
  ifstream lfile("lastname.txt");
  string lname;

  while (getline(lfile, lname)) {
    if (!lname.empty()) {
      lastName.push_back(lname);
    }
  }
  lfile.close();

  if (firstName.empty() || lastName.empty()) {
    cout << "files missing or empty" << endl;
    return;
  }

  //generate random students
  for (int i = 0; i < count; i++) {
    string rf = firstName[rand() % firstName.size()];
    string rl = lastName[rand() % lastName.size()];
    Student* s = new Student;
    //put name into array
    strcpy(s->fname, rf.c_str());
    strcpy(s->lname, rl.c_str());
    s->id = nextId;
    nextId++;
    //random gpa
    int g = rand() % 401;
    s->gpa = g / 100.0f;
    insertStudent(s, table);
  }

  cout << "Generate " << count << " random students" << endl;
}
