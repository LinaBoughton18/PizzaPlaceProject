#ifndef FINALPIZZAPROJECT_ORDER_HPP
#define FINALPIZZAPROJECT_ORDER_HPP

#include <string>
#include "Time.hpp"
using namespace std;

class Order {
public:
    //Pre: proper hour and minute parameters are given (as well as the info)
    //Post: A new order is created with the given data
    Order(Time t, string inf);
    //Pre: None
    //Post: Destructs the object and deallocates the memory
    ~Order();

    //Pre: None
    //Post: returns the order time as a class time
    Time getTime();
    //Pre: None
    //Post: returns the order info as a string
    string getInfo();

    //Pre: None
    //Post: sets the order info to inf
    void setInfo(string inf);
private:
    Time time;
    string info;
};

Order::Order(Time t, string inf) { time = t; info = inf; }
Order::~Order() {}

Time Order::getTime() { return time; }
string Order:: getInfo() { return info; }

void Order::setInfo(string inf) { info = inf; }

#endif //FINALPIZZAPROJECT_ORDER_HPP
