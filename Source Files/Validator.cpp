#include "Validator.h"

ValidatorException::ValidatorException(std::string _message) : message(_message) {}

const char *ValidatorException::what() const noexcept {
    return message.c_str();
}

bool validateDate(const std::string &date) {
    if (date.size() != 16) {
        return false;
    }
    int day = std::stoi(date.substr(0, 2));
    if (day < 0 || day > 31) {
        return false;
    }
    int month = std::stoi(date.substr(3, 2));
    if (month < 0 || month > 12) {
        return false;
    }
    int year = std::stoi(date.substr(6, 4));
    int hour = std::stoi(date.substr(11, 2));
    if (hour < 0 || hour > 23) {
        return false;
    }
    int minute = std::stoi(date.substr(14, 2));
    if (minute < 0 || minute > 59) {
        return false;
    }
    if ((year % 4 != 0 && month == 2 && day > 28) or (year % 4 == 0 && month == 2 && day > 29)){
        return false;
    }

    return true;
}

void Validator::validate(const Event &e) {
    std::string errors;
    std::string link = e.getLink();
    if (e.getTitle().size()<3)
        errors += string("Event title must have at least 3 characters!\n");
    if (e.getDescription().empty())
        errors += string("Event must have a description!\n");
    if(!validateDate(e.getDateAndTime()))
        errors += string("Date is not correct!(dd/mm/yyyy hh:mm)\n");
    if(link.find("https://")!=0 and link.find("www.")!=0)
        errors += string("Event link must start with https:// or www.!\n");
    
    if (!errors.empty()){
        throw ValidatorException(errors);
    }
}

