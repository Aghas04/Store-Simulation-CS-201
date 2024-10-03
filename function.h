#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "LinkedList.h"
#include "Queue.h"

/*
void emptyCheckoutLines(vector<Queue*> lines, int minutes) {
  for (int i = 0; i < lines.size(); i++) {  //looping through the all the checkout lines
    
    if (lines[i]->empty()) {
      lines[i]->setTempCustomer(listType()); //assign empty customer to the temp customer
      continue;
    } else if (lines[i]->peek().cartId == lines[i]->getTempCustomer().cartId) { //if the top of the line (person checking out) is the same as the temp customer
      if (lines[i]->getTempCustomer().checkoutTime == minutes) {  //if the temp person's checkout time is the same as the current minute
        lines[i]->delElement(); //removes customer from queue (check out the customer)
        //cout << "Checked out person B-)" << endl;
        }
      continue; //if they are the same, but not ready to check out, continue to the next line
      } else {  //if the top of the line (person checking out) is not the same as the temp customer
          lines[i]->setTempCustomer(lines[i]->peek()); //make them the tempCustomer
          lines[i]->setTempCustomerCheckoutTime(lines[i]->peek().enterQTime + (ceil(static_cast<double>(lines[i]->peek().itemCount) * 0.15))); //assign them a check out time
        }
  }
}
*/

void emptyCheckoutLines(vector<Queue*> lines, int minutes, int& checked) {
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i]->empty()) {
      lines[i]->IncTempCustomerIdleTime();
     // idleLines++;//increment idle time 
      // Handle case when checkout line is empty
      // Clear temp customer
      lines[i]->setTempCustomer(listType()); // Assuming listType() provides an empty/default state
      continue;
    }

    // Update temp customer if needed
    if (lines[i]->peek().cartId != lines[i]->getTempCustomer().cartId) {
      lines[i]->setTempCustomer(lines[i]->peek());
      lines[i]->setTempCustomerCheckoutTime(minutes);
    } //when they are at the point of check out their time it takes to check out should be added to the current minutes this is done in the Queue funtion "setTempCustomerCheckoutTime

    // Check if temp customer is ready to be deleted from Queue
    if (lines[i]->getTempCustomer().checkoutTime == minutes) {
      lines[i]->delElement();
      //cout << "Checked out person B-)" << endl;
      // Clear temp customer after checkout
      lines[i]->setTempCustomer(listType());
    }
   if (minutes > 720) {
     lines[i]->IncTempCustomerOvertime();
   }
    //beg
  /*if (lines[i]->getLineLength() > lines[i]->maxLineLength) {
    lines[i]->maxLineLength = lines[i]->getLineLength();
    }
    */
    //end
  }
}