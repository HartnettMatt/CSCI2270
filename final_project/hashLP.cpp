#include "hashLP.hpp"
using namespace std;

hashLP::hashLP(){
  tableSize = 10009;
  table = new int[tableSize];
}

// inserts a key into hash table
bool hashLP::insertItem(int key){
  int index = hashFunction(key);
  if(table[index] == 0){
    table[index] = key;
    return true;
  } else {
    for(int i = index+1; i != index; i++){
      if(i == tableSize){
        i = 0;
      }
      if(table[i] == 0){
        table[i] = key;
        return true;
      }
    }
  }
  return false;
}

// hash function to map values to key
unsigned int hashLP::hashFunction(int key)
{
    return (key % tableSize);
}

void hashLP::printTable(){
  for (int i = 0; i < tableSize; i++) {
    cout << i <<" || " << table[i] << endl;;
  }
}
void hashLP::print100(){
  for (int i = 0; i < 100; i++) {
    cout << i <<" || " << table[i] << endl;;
  }
}

int hashLP::searchItem(int key){
  int index = hashFunction(key);
  if(table[index] == key){
    return index;
  } else {
    for(int i = index+1; i != index; i++){
      if(i == tableSize){
        i = 0;
      }
      if(table[i] == key){
        return i;
      }
    }
  }
  return -1;
}

bool hashLP::deleteItem(int key){
  int index = hashFunction(key);
  if(table[index] == key){
    table[index] = -1;
    return true;
  } else {
    for(int i = index+1; i != index; i++){
      if(i == tableSize){
        i = 0;
      }
      if(table[i] == key){
        table[i] = -1;
        return true;
      }
    }
  }
  return false;
}