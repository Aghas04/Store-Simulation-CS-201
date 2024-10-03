#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

struct listType{
  int cartId; //unique id assigned for each cart
  int itemCount; //amount of items the customer will get (randomly generated)
  int enterQTime; //current ‘time’ + shopping time
  int checkoutTime; //checkout time = itemCount * 15 - initialized after they have gotten their items.
  int idleTime = 0;
  int overTime = 0;
};

struct Node {
  listType data;
  Node* nextPtr;
};


class LinkedList {
protected:
  Node* headPtr;
  Node* tailPtr;
public:
  LinkedList();
  LinkedList(listType);
  virtual ~LinkedList();
  Node* getheadpointer() {
    return headPtr;
  }
  bool empty() {
    return headPtr == nullptr;
  }
//added virtual becasue they will act differnt
  void virtual addElement(listType); //add cart information to the list (list should probably be ordered)
  void virtual delElement(); //remove a node item from the front of the list
  bool listIsEmpty(); //return true if the list is empty (headPtr = nullptr?), false otherwise
  listType virtual peek(); //return the contents of the front of the list (but do not remove)
  void printList();
  static int listCount; 
  
};


listType genorateCustomer(int ID,int time);


