#ifndef FINALPIZZAPROJECT_TIME_HPP
#define FINALPIZZAPROJECT_TIME_HPP

#include <stdexcept>
#include <iostream>
#define MINUTE_PER_HOUR 60
using namespace std;

class Time {
protected:
    int hour, minute;
public:
    Time();
    Time(int h, int m);
    ~Time();
    static int elapsedMin(Time t1, Time t2);
    string toString();
};

//Pre: none
//Post: Creates a time with the given hour and minute.
Time :: Time(): hour(0) , minute(0) {}

//Pre: The hours should be entered correctly
//Post: Creates a time with the given hour and minute
Time :: Time(int h, int m) {
    while (h < 0 || h > 23 || m < 0 || m > 59) {
        cout << "Error: Time is not entered correctly, please renter: [hour:minute] (including semicolon)" << endl;
        char semi;
        cin >> h >> semi >> m;
    }
    hour = h;
    minute = m;
}

Time :: ~Time() {}

//Pre: none
//Post: Returns the difference in minutes between t1 and t2.
int Time :: elapsedMin(Time t1, Time t2) {
    int minutes1 = (t1.hour * MINUTE_PER_HOUR) + t1.minute;
    int minutes2 = (t2.hour * MINUTE_PER_HOUR) + t2.minute;

    return abs(minutes1 - minutes2);
}

//Pre: none
//Post: Returns a string containing the hour and minute
string Time :: toString() {
    string timer = to_string(hour) + ":" + to_string(minute);
    return timer;
}

#endif //FINALPIZZAPROJECT_TIME_HPP
