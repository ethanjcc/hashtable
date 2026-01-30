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
}
