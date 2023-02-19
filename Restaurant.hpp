#ifndef FINALPIZZAPROJECT_RESTAURANT_HPP
#define FINALPIZZAPROJECT_RESTAURANT_HPP

#include <string>
#include "Time.hpp"
#include "Order.hpp"
#include "Driver.hpp"
#include <deque>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Restaurant {
public:
    Restaurant();
    ~Restaurant();
    void addOrder(string in_info, Time in_time);
    void serve();
    void status();
    Order * getLastServed();
    Order * getLastOrder();

private:
    deque<Order*> ordersToServe;
    deque<Order*> ordersToDepart;
    bool OrderDepart = false;

    /**
     * Template function to clear a double-ended queue with heap-allocated elements
     * @tparam T
     * @param in_deque
     *
     * @pre None
     * @post Deallocates all pointers in in_deque
     */
    template<template<typename> class T, class P>
    void clearContainer(T<P> in_container)
    {
        for_each(in_container.begin(), in_container.end(), [](auto i){delete i;});
        in_container.clear();
    }
};

/**
* @pre None
* @post Adds order (with info set to in_info and time set to in_time) to the cooking queue
* @param in_info
* @param in_time
*/
void Restaurant::addOrder(std::string in_info, Time in_time)
{
    auto newOrderPtr = new Order(in_time, in_info);
    ordersToServe.push_back(newOrderPtr);
    cout << "Added " << in_info << " to the orders waiting to be served/cooked." << endl;
}

/**
* @pre Container ordersToServe is not empty
* @post Takes first order from ordersToServe and puts it at the end of ordersToDepart
*/
void Restaurant::serve()
{
    if (ordersToServe.empty()) {
        cout << "There are no orders to be served." << endl;
    }
    else {
        ordersToDepart.push_back(ordersToServe.front());
        cout << "Serve " << ordersToServe.front()->getInfo() << endl;
        ordersToServe.pop_front();
    }
}

/**
* @pre None
* @post prints a list of orders waiting to cook, a list of orders waiting to depart and
* a list of logged-in drivers and their status, including any orders they are delivering
*/
void Restaurant::status()
{
    cout << "Orders to be served:\n";
    for(auto it = ordersToServe.begin(); it != ordersToServe.end(); it++)
    {
        cout << (*it)->getInfo() << "\n";
    }

    cout << "Orders to be delivered:\n";

    for(auto it = ordersToDepart.begin(); it != ordersToDepart.end(); it++)
    {
        cout << (*it)->getInfo() << "\n";
    }

}

/**
* @pre None
* @post prints out:
* -   total number of deliveries completed
* -   average time per order (from “order” to “deliver”)
* -   number of deliveries completed by each driver
* -   average time per completed delivery for each driver (from “depart” to “deliver”)
* -   total driving time on completed trips for each driver (from “depart” to “return”)
* -   total tips received by each driver
*/

Restaurant::Restaurant()
{
    ordersToServe = deque<Order*>();
    ordersToDepart = deque<Order*>();
}

/**
* Destructor for Restaurant Class
* @pre None
* @post Deallocates drivers, ordersToServe and ordersToDepart
*/
Restaurant::~Restaurant()
{

    for_each(ordersToDepart.begin(), ordersToDepart.end(), [](auto i){delete i;});
    ordersToDepart.clear();

    for_each(ordersToDepart.begin(), ordersToDepart.end(), [](auto i){delete i;});
    ordersToDepart.clear();
}

//Pre: None
//Post: returns the first element in the ordersToDepart queue.
// Deletes the first element off of that queue as well.
Order *Restaurant::getLastServed()
{
    if (ordersToDepart.empty()) {
        return nullptr;
    }
    Order* temp = ordersToDepart.front();
    ordersToDepart.pop_front();
    return temp;
}

#endif //FINALPIZZAPROJECT_RESTAURANT_HPP
