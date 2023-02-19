#include <iostream>
#include <string>
#include <iomanip>
#include "Time.hpp"
#include "Restaurant.hpp"
#include "Driver.hpp"
#include <unordered_map>
using namespace std;

//Pre: None
//Post: The commands are printed in the ostream.
void printCommands();


int main() {
    unordered_map<string, Driver> drivers;
    Restaurant D;
    char command, semi;
    string driver, info;
    int hour, min;
    int totalOrderTime = 0, totalDeliveries = 0;
    float tip;

    cout << "Welcome to Dominato's Computerized Delivery System!" << endl << endl;
    printCommands();

    do {
        //Gets a one letter command from the user input
        cout << endl << "Awaiting command: ";
        cin >> command;
        command = tolower(command);

        //Executes the proper commands
        switch (command) {
            case 'h':
                printCommands();
                break;
            case 'i':
                cin >> driver;
                drivers[driver].login();
                break;
            case 'o':
                cin >> driver;
                drivers[driver].logout();
                break;
            case '+':
                cin >> hour >> semi >> min >> info;
                D.addOrder(info, Time(hour, min));
                break;
            case '=':
                cin >> hour >> semi >> min;
                D.serve();
                break;
            case '>':
                cin >> hour >> semi >> min >> driver;
                drivers[driver].depart(Time(hour, min), D.getLastServed());
                break;
            case '-':
                cin >> hour >> semi >> min >> driver >> tip;
                drivers[driver].deliver(Time(hour, min), tip);
                break;
            case '<':
                cin >> hour >> semi >> min >> driver;
                drivers[driver].arrive(Time(hour, min));
                break;
            case '@':
                cout << endl;
                cout << "-----Status-----" << endl;
                //Print Restaurant Status
                D.status();

                //Prints Driver Status
                cout << endl << "Driver Status" << endl;
                for (auto it = drivers.begin(); it != drivers.end(); it++) {
                    cout << it->first << " " << it->second.getStatus() << endl;
                }
                break;
            case 's':
                cout << "-----Summary-----" << endl;
                totalOrderTime = 0;
                totalDeliveries = 0;

                //Prints driver summaries
                for (auto it = drivers.begin(); it != drivers.end(); it++) {
                    cout << it->first << ":" << endl;
                    it->second.getSummary(&totalDeliveries, &totalOrderTime);
                }

                cout << endl << "Total Deliveries: " << totalDeliveries << endl;
                cout << "Average Time per Order: " << totalOrderTime/totalDeliveries << endl;

                break;
            case 'q':
                break;
            default:
                cout << "Command not recognized. Please try again." << endl;
        }
    } while (command != 'q');

    cout << "Thank you for using Dominato's Computerized Delivery System! Goodbye!" << endl;
    return 0;
}

void printCommands() {
    cout << "Commands are given in lowercase, variables in capital:" << endl;
    cout << "h : Help, displays this message" << endl;
    cout << "i DRIVER : login DRIVER" << endl;
    cout << "o DRIVER : logout DRIVER" << endl;
    cout << "+ HOUR:MINUTE INFO : adds a new order with TIME and INFO" << endl;
    cout << "= HOUR:MINUTE : serves an order, readies it for delivery, at TIME" << endl;
    cout << "> HOUR:MINUTE DRIVER : departs DRIVER at TIME to deliver the most recently served order" << endl;
    cout << "- HOUR:MINUTE DRIVER TIP : DRIVER has delivered their order at TIME and received a TIP" << endl;
    cout << "< HOUR:MINUTE DRIVER : DRIVER has arrived at TIME" << endl;
    cout << "@ : view the orders waiting to cook, orders waiting to depart, and the status of all the drivers" << endl;
    cout << "s : view the total number of delivers completed, average time per completed delivery per driver"
            "average time per order, total driving time per driver, total tips per driver, and login status" << endl;
    cout << "q : quits the program" << endl;
}

//Test Commands
// i Lina + 1:00 pizza1 i Tasin i Jorge + 1:01 pizza2 = 1:05 > 1:07 Lina = 1:13 + 1:16 pizza3 = 1:18 > 1:20 Tasin - 1:25 Lina 3.05 + 1:27 pizza4
// i Bev + 18:00 mushroom1 + 18:02 spinach2 i Abe = 18:20 > 18:20 Abe = 18:28 - 18:30 Abe 2.00 + 18:30 cheese1 > 18:31 Bev < 18:40 Abe o Abe
// +1:00 pizza1 +1:05 pizza2 =1:10 i Dan > 1:11 Dan =1:20 i Ada > 1:25 Ada
// - 1:32 Dan 2.50 < 1:46 Dan - 1:50 Ada 5.10 < 2:00 Ada +2:03 pizza3 =2:10
// > 2:14 Dan -2:25 Dan 3.75 < 2:37 Dan