#pragma once
#include "LinkedList.h"
using namespace std;

//create a children class of linked for queue
class Queue : public LinkedList {
protected:
  listType tempCustomer;
public:
  static int lineLength;
  virtual ~Queue() {

  }
  listType getTempCustomer() {
    return tempCustomer;
  }
  void setTempCustomer(listType customer) {
    tempCustomer.cartId = customer.cartId;
    tempCustomer.itemCount = customer.itemCount;
    tempCustomer.checkoutTime = customer.checkoutTime;
  }
  void IncTempCustomerIdleTime() {
    tempCustomer.idleTime++;
  }
  void IncTempCustomerOvertime() {
    tempCustomer.overTime++;
  }
  void setTempCustomerCheckoutTime(int minutes) {
    tempCustomer.checkoutTime = minutes + (ceil(static_cast<double>(tempCustomer.itemCount) * 0.15));
  }
  void addElement(listType d) {
    Node* newNode = new Node;
    newNode->data = d;
    newNode->nextPtr = nullptr;
    if (headPtr == nullptr) {
      headPtr = newNode;
      tailPtr = newNode;
    } else {
      tailPtr->nextPtr = newNode;
      tailPtr = newNode;
    }
    lineLength++;
  }
  int getLineLength() {
    Node* currentNode;
      currentNode = getheadpointer();

      int lineLength = 0;

      // Loop until you reach the end of the Queue

      // find the size of the current lane
      while (currentNode != nullptr) {
        // Access the data in the current node
        //listType data = currentNode->data;
        lineLength ++;

        // Move to the next node
        currentNode = currentNode->nextPtr;
      }
    return lineLength;
  }
//make sure queue is not empty then delete
  void delElement() {
    Node* delNode = headPtr;
    if (delNode == nullptr) {
      cout << "WARNING: Queue is empty!" << endl;
      return;
    }
    headPtr = delNode->nextPtr;
    delete delNode;
    lineLength--;
  }
  listType peek() {
    // Check if the list is empty
    if (headPtr == nullptr) {
      cout << "The list is empty." << endl;
      // Return a default listType object
      return listType();
    }

    // Return the data of the head node
    return headPtr->data;
  }
  

};




