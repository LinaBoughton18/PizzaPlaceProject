#ifndef FINALPIZZAPROJECT_DRIVER_HPP
#define FINALPIZZAPROJECT_DRIVER_HPP

#include "Time.hpp"
#include "Order.hpp"
#include <string>
#include <deque>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

class Driver {
public:
    Driver();
    ~Driver();

    void depart(Time time, Order* order);
    void deliver(Time time, float tip);
    void arrive(Time time);
    void logout();
    void login();

    int getTotalDeliveries();
    int getTotalMinDelivering();
    int getTotalMinDriving();
    float getTotalTips();
    string getStatus();
    void getSummary(int *totalDeliveries, int *tOrderTime);

private:
    int deliveryCount = 0;
    float tips = 0.00;
    bool loggedIn = false;
    bool delivering = false;

    Time orderTime;
    Time departTime;
    Time deliverTime;
    Time arriveTime;
    Order* myOrder = 0;


    int totalDrivingTime = 0; //from depart to arrive
    int totalOrderTime = 0; //from order to deliver
    int totalDeliveryTime = 0; //from depart to deliver
};

//Pre: none
//Post: constructs a new driver object
Driver::Driver() {}
//Pre: none
//Post: destructs a driver object
Driver::~Driver() {}

//Pre: A driver is not already logged in.
//Post: Changes an unlogged in driver to logged in.
// Sends an error message if the preconditions are not met.
void Driver::login() {
    if (loggedIn) {
        cout << "Error: Driver already logged in." << endl;
    }
    else {
        loggedIn = true;
        cout << "Logged in." << endl;
    }
}

//Pre: A driver that is logged in and is not delivering/
//Post: Logs out a driver. Sends an error message if the preconditions are not met.
void Driver::logout() {
    if (!loggedIn)
    {
        cout << "Error: Driver already logged out." << endl;
    }
    else if (delivering) {
        cout << "Error: Driver cannot logout while delivering." << endl;
    }
    else
    {
        loggedIn = false;
        cout << "Logged out." << endl;
    }
}

//Pre: A driver who is logged in and not delivering an order.
//Post: Signals that the driver is now delivering, changes the myOrder pointer to
// point towards their order and sets some time-based variables.
// Sends an error message if the preconditions are not met.
void Driver::depart(Time time, Order* order) {
    if (!loggedIn) {
        cout << "Error: Driver is logged out." << endl;
    }
    else if (delivering) {
        cout << "Error: Driver already delivering an order." << endl;
    }
    else if (order == nullptr){
        cout << "Error: Nothing to depart" << endl;
    }
    else {
        myOrder = order;
        orderTime = myOrder->getTime();
        delivering = true;
        departTime = time;
        cout << "Confirmed departure with " << myOrder->getInfo() << endl;
    }
}

//Pre: A driver who is logged in and is delivering a pizza.
//Post: Gets rid of the driver's pizza, adds to their tip total, and calculates the total-driving and
// total-delivery times. Increments the delivery count.
//Sends error messages if the driver has already delivered a pizza, is delivering, or is logged out.
void Driver::deliver(Time time, float tip) {
    if (!loggedIn || !delivering || myOrder == 0) {
        cout << "Error: Driver is logged out or is currently not delivering." << endl;
    }
    else if (myOrder == 0) {
        cout << "Error: Driver does not have an order to deliver." << endl;
    }
    else {
        deliveryCount++;
        deliverTime = time;
        tips = tips + tip;
        totalOrderTime = totalOrderTime + time.elapsedMin(deliverTime, orderTime);
        totalDeliveryTime = totalDeliveryTime + time.elapsedMin(deliverTime, departTime);
        totalDrivingTime = totalDrivingTime + time.elapsedMin(deliverTime, departTime);

        cout << "Confirmed delivery of " << myOrder->getInfo() << endl;
        delete myOrder;
        myOrder = 0;
    }
}

//Pre: A driver who is logged in and is returning from delivering a pizza.
//Post: Changes the driver's status of delivering to false. Calculates total driving time.
// Sends a message if the driver is not delivering currently or is logged out.
void Driver::arrive(Time time) {
    if (!loggedIn) {
        cout << "Error: Driver is logged out." << endl;
    }
    else if(!delivering) {
        cout << "Error: Driver is not currently delivering." << endl;
    }
    else {
        delivering = false;
        arriveTime = time;
        cout << "Confirmed driver arrival." << endl;
        totalDrivingTime = totalDrivingTime + time.elapsedMin(arriveTime, deliverTime);
    }
}

//Ian's Functions

/*
* Pre: None
* Post: Returns the total number of completed deliveries.
*/
int Driver::getTotalDeliveries() {
    return deliveryCount;
}

/*
* Preconditions: None
* Postcondition: Returns the total minutes spent delivering (i.e., between
*                “order" and deliver” commands).
*/
int Driver::getTotalMinDelivering() {
    return totalOrderTime;
}

/*
* Preconditions: None
* Postcondition: Returns the total minutes spent driving (i.e., between
*                “depart” and “arrive” commands).
*/
int Driver::getTotalMinDriving() {
    return totalDrivingTime;
}

/*
* Pre: None
* Post: Returns the total tips received, in dollars
*/
float Driver:: getTotalTips() {
    return tips;
}

/*
* Preconditions: None
* Postcondition: Returns a string containing the driver’s name, state
*                (e.g., not logged in), and, if the driver is delivering an
*                order, the departure time and toString of the order being delivered.
*/
string Driver::getStatus() {
    string status = "Logged out.";

    if (loggedIn) {
        status = "Logged in.";

        if (delivering && myOrder != 0) {
            status = status + " Currently delivering " + myOrder->getInfo();
        }
        else if (delivering) {
            status = status + " Returning from delivering an order.";
        }
    }

    return status;
}

//Pre: none
//Post: prints out the total deliveries made. If that count is higher than 0,
//prints out the driver's total tips, average time delivering, and average time driving.
//Then increments the two pointers given to it to be output into the total summary.
void Driver::getSummary(int *totalDeliveries, int *tOrderTime) {
    cout << "     Total Deliveries Made: " << deliveryCount << endl;

    if (deliveryCount != 0) {
        cout << "     Total Tips Made: " << setprecision(3) << tips << endl;
        cout << "     Average Time Delivering: " << totalDeliveryTime/deliveryCount << endl;
        cout << "     Average Time Driving: " << totalDrivingTime/deliveryCount << endl;

        *totalDeliveries = *totalDeliveries + deliveryCount;
        *tOrderTime = *tOrderTime + totalOrderTime;
    }
}

#endif //FINALPIZZAPROJECT_DRIVER_HPP
