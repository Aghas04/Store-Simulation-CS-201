#include "LinkedList.h"

int LinkedList::listCount = 0;


LinkedList::LinkedList() {
  //cout << "CONSTRUCTOR\n";
  headPtr = nullptr;
  tailPtr = nullptr;
}
LinkedList::LinkedList(listType d){
  //cout << "CONSTRUCTOR\n";
  Node* tempPtr = new Node;
  tempPtr->data = d;
  tempPtr->nextPtr = nullptr;
}
LinkedList::~LinkedList() {
   //cout << "DESTRUCTOR\n";
}
//create a fucntion to add node
void LinkedList::addElement(listType d) {
  // Create a new node
  Node* newNode = new Node;
  newNode->data = d;
  newNode->nextPtr = nullptr;

  // If the list is empty, add the new node as the first node
  if (headPtr == nullptr) {
    headPtr = newNode;
  } else {
    // If the new node's enterQTime is less than the head node's enterQTime,
    // add the new node before the head node
    if (newNode->data.enterQTime < headPtr->data.enterQTime) {
      newNode->nextPtr = headPtr;
      headPtr = newNode;
    } else {
      // Otherwise, find the correct position in the list to insert the new node
      Node* tempNode = headPtr;
      while (tempNode->nextPtr != nullptr && tempNode->nextPtr->data.enterQTime <= newNode->data.enterQTime) {
        tempNode = tempNode->nextPtr;
      }
      // Insert the new node at the correct position
      newNode->nextPtr = tempNode->nextPtr;
      tempNode->nextPtr = newNode;
    }
  }
  listCount++;
}


void LinkedList::delElement() {
  // Check if the list is empty
  if (headPtr == nullptr) {
    cout << "The list is already empty." << endl;
    return;
  }

  // Save the current head node in a temporary pointer
  Node* tempPtr = headPtr;

  // Move the head pointer to the next node
  headPtr = headPtr->nextPtr;

  // If the list is now empty, also update tailPtr
  if (headPtr == nullptr) {
    tailPtr = nullptr;
  }
  --listCount;
  // Delete the old head node
  delete tempPtr;
  tempPtr = nullptr;
}


listType LinkedList::peek() {
  // Check if the list is empty
  if (headPtr == nullptr) {
    cout << "The list is empty." << endl;
    // Return a default listType object
    return listType();
  }

  // Return the data of the head node
  return headPtr->data;
}


void LinkedList::printList() {
  //print the first last name and age
  Node* tempPtr = headPtr;
  while (tempPtr != nullptr) {
    cout << tempPtr-> data.cartId << " " << tempPtr->data.itemCount << " " << tempPtr->data.enterQTime << endl;
    tempPtr = tempPtr->nextPtr;
  }

}


listType genorateCustomer(int ID, int times) {
  
  listType customer;
  int items = 0;
  double totaltime = 0.0;
  customer.cartId = ID;
  int random = (rand() % 10) + 1;
  if (random <= 4 && random >= 1) {
    items = (rand() % 10) + 1;
  }
  else if (random <= 7 && random > 4) {
    items = (rand() % 10) + 11;
  }
  else if (random == 9 || random == 8) {
    items = (rand() % 10) + 21;
  }
  else if (random == 10) {
    items = (rand() % 29) + 31;
  }
  customer.itemCount = items;
  for (int i = 0; i < items; i++) {
    double timei = (rand() % 31) + 30;
    totaltime += timei;
  }
  totaltime /= 60;
  totaltime += times;
  customer.enterQTime = static_cast<int>(totaltime);
  customer.checkoutTime = ceil(static_cast<double>(items) * 0.15);
  return customer;
}