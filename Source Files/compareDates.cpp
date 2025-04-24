#include <string>
#include "Event.h"

using namespace std;

bool compareDates(const Event &event1, const Event &event2) {
    auto date1 = event1.getDateAndTime();
    auto date2 = event2.getDateAndTime();

    int day1 = std::stoi(date1.substr(0, 2));
    int day2 = std::stoi(date2.substr(0, 2));

    int month1 = std::stoi(date1.substr(3, 2));
    int month2 = std::stoi(date2.substr(3, 2));

    int year1 = std::stoi(date1.substr(6, 4));
    int year2 = std::stoi(date2.substr(6, 4));

    int hour1 = std::stoi(date1.substr(11, 2));
    int hour2 = std::stoi(date2.substr(11, 2));

    int minute1 = std::stoi(date1.substr(14, 2));
    int minute2 = std::stoi(date2.substr(14, 2));

    // Compare years
    if (year1 < year2)
        return true;
    else if (year1 > year2)
        return false;

    // Compare months
    if (month1 < month2)
        return true;
    else if (month1 > month2)
        return false;

    // Compare days
    if (day1 < day2)
        return true;
    else if (day1 > day2)
        return false;

    if (hour1 < hour2)
        return true;
    else if (hour1 > hour2)
        return false;

    if (minute1 < minute2)
        return true;
    else if (minute1 > minute2)
        return false;

    return false;
}