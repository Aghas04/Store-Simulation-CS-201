//NAME: Victor Olatunji, Alex Ghasemi, Luis Sanchez
//DATE: 04/28/2024
//PGM 14: Store Simulation

#include "function.h"
#include <vector>
#include <limits>
using namespace std;



int main() {
  vector<int> customersHelped;
  // tracks number of customers that passed through a specific checkout lane
  vector<int> itemsinline;
  // tracks number of items that passed through a specific checkout lane
  vector<int> maxline;
  // tracks the longest length a specifc checkout lane had
  vector<double> totalidletime;
  // tracks the idel time of a specific checkout lane
  vector<double> totalovertime;
  // tracks the overtime of a specific checkout lane

  
  srand(time(0));
  int minutes = 0;
  int ID = 10000, people = 0, items = 0;
  int checked = 0;
  int lanes = 0;
  vector<Queue *> checkoutLanes;
  listType customer;

  LinkedList Shopping;
  cout << "How many Checkout Lanes (Int 1-25): ";
  cin >> lanes;
  

  // Validate input type
  while (cin.fail()) {
      cout << "\nInvalid input type. Enter an integer: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> lanes;
  }

  // Validate range
  while (lanes < 1 || lanes > 25) {
      cout << "Lanes is out of range." << endl;
      cout << "Enter a number between 1 and 25: ";
      cin >> lanes;
      while (cin.fail()) {
        cout << "\nInvalid input type. Enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> lanes;
    }
  }

  cout << endl << endl;
  customersHelped.resize(lanes);
  itemsinline.resize(lanes);
  maxline.resize(lanes);
  totalidletime.resize(lanes);
  totalovertime.resize(lanes);

  // create the number of checkout lanes the user requests
  for (int i = 0; i < lanes; i++) {
    Queue *Checkout1 = new Queue;
    checkoutLanes.push_back(Checkout1);
    
  }
  while (true) {
    if (minutes < 720) {
      int randCustomer = rand() % 3;
      if (randCustomer == 0) {
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);
      } else if (randCustomer == 1) {
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);
        // ADD to Linked List based on Qtime
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);

      } else if (randCustomer == 2) {
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);
        customer = genorateCustomer(ID, minutes);
        ID += 1;
        people += 1;
        items += customer.itemCount;
        Shopping.addElement(customer);
      }
    }
    while (!Shopping.empty() && Shopping.peek().enterQTime <= minutes) {
      int mintime = 0;
      double minTotalTime = 9999999990.0;
      double totaltime;
      Node *currentNode;
      for (int t = 0; t < checkoutLanes.size(); t++) {
        // Start from the head of the Queue
        currentNode = checkoutLanes[t]->getheadpointer();

        totaltime = 0.0;

        // Loop until you reach the end of the Queue

        // find the size of the current lane
        while (currentNode != nullptr) {
          // Access the data in the current node
          listType data = currentNode->data;
          totaltime += static_cast<double>(data.itemCount) * 0.15;
         
          // Move to the next node
          currentNode = currentNode->nextPtr;
        }
        //beg of test of lanes and time of lanes
        /*if (minutes == 700) {
          cout << Shopping.peek().enterQTime << " : " << Shopping.peek().itemCount << endl;
          cout << "Lane: " << t << " total: " << totaltime << endl;
        }
        if (minutes == 701) {
          cout << Shopping.peek().enterQTime << " : " << Shopping.peek().itemCount << endl;
          cout << "Lane: " << t << " total: " << totaltime << endl;
        }*/

        //end of test
        // cout << t << ": total : " << totaltime << endl;
        if (totaltime <= minTotalTime) {
          
          minTotalTime = totaltime;
          mintime = t;
        }
      }
      
      if(totalovertime[mintime] - 720 > 0){
        totalovertime[mintime] = totalovertime[mintime] - 720;
      }
      //find the total overtime each iteration
      
      
      
      checkoutLanes[mintime]->addElement(Shopping.peek());
      totalovertime[mintime] += static_cast<double>(Shopping.peek().itemCount) * 0.15;
      
      
      if ((checkoutLanes[mintime]->getLineLength()) > maxline[mintime]) {
        maxline[mintime] = (checkoutLanes[mintime]->getLineLength());
        // if the lane currently being updated is going to be of a greater size
        // than it has been throughout the duration of the program, set maxline
        // to this new size
      }

      customersHelped[mintime] += 1; // increment #of customers in the lane
      itemsinline[mintime] += Shopping.peek().itemCount; // increment # of items in the lanes
      //items += itemsinline[mintime];
      Shopping.delElement();
    }

    bool qEmpty = true;

    for (int i = 0; i < checkoutLanes.size(); i++) {
      if (!checkoutLanes[i]->empty()) {
        qEmpty = false;
        break;
      }
    }

    if (qEmpty && Shopping.empty()) {
      break;
    } else {
      emptyCheckoutLines(checkoutLanes, minutes, checked);
      minutes += 1;
      // how are we keeping track of when a specific checkout lane is empty -
      // this just empties all lanes generally?
    }
    // Start from the head of the Queue
   /*Node *currentNode = Shopping.getheadpointer();

    // Loop until you reach the end of the Queue
    while (currentNode != nullptr) {
      // Access the data in the current node
      listType data = currentNode->data;

      cout << data.cartId << " " << data.itemCount << " " << data.enterQTime
           << " " << data.checkoutTime << endl;

      // Move to the next node
      currentNode = currentNode->nextPtr;
    }*/
    
  }

  // cout << "Customers checked out: "<< checked << endl; <- this is incrimented
  // in the emptyCheckoutLines function. maybe could make a attribute in the
  // listType struct named customersHelped and then increment in the
  // emptyCheckOutLines function when a customer is deleted. this would give
  // each checkout lane their own total customers helped.

  /*

  Now we just have to impliment the statistics incrimentation in the main while
  loop so that the print at the end of main has values. Right now (1:16p,
  Tuesday, April 23) the queue in line are getting emptied because they are
  getting checked out then there are no customers in the vector after main while
  loop is done. -Luis

  */

  
  //cout << "People: " << people << endl;
  //cout << "Items: " << items << endl;
  
  for (int i = 0; i < checkoutLanes.size(); i++) {
    cout << endl;
    cout << "Checkout lane " << i + 1 << ": " << endl << endl;    
    cout << "Total Customers Helped: " << customersHelped[i] << endl;
    cout << "Total Number of Items: " << itemsinline[i] << " items" << endl;
    cout << "Max Line Length: " << maxline[i] << " customers in line" << endl;
    cout << "Total Idle Time: " << checkoutLanes[i]->getTempCustomer().idleTime << " minutes" << endl;
    cout << "Total Over Time: " <<  checkoutLanes[i]->getTempCustomer().overTime << " minutes" << endl;
    }
    
    /*
    Statistics:
    DONE - cout << "Total Customers Helped: " << totalCustomersLineN << "
  customers" << endl; 
    DONE - cout << "Total Number of Items: " <<
  totalItemsLineN << " items" << endl; 
    DONE - cout << "Max Line Length: " <<
  maxLineLengthLineN << " customers in line" << endl;
    DONE - cout << "Total Idle
  Time: " << totIdleTimeLineN << " minutes" << endl;
    DONE - cout << "Total Over
  Time: " << totOverTimeLineN - totTimeLineN<< " minutes" << endl;


  }*/
    // cout << "Total Time: " << minutes << " minutes" << endl;

  // cout << checkoutLanes[0]->peek().cartId << " " <<
  // checkoutLanes[0]->peek().itemCount << " " <<
  // checkoutLanes[0]->peek().enterQTime << " " <<
  // checkoutLanes[0]->peek().checkoutTime << endl;
}