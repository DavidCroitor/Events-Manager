#include <cstring>
#include <iostream>
#include "Event.h"
#include "Utils.h"
#include <vector>

using namespace std;

Event::Event() {
    this->title = "";
    this->description = "";
    this->date_and_time = "";
    this->number_of_people = 0;
    this->link = "";
}

Event::Event(const string &title, const string &description, const string &date_and_time, int people,
             const string &link) {
    this->title = title;
    this->description = description;
    this->date_and_time = date_and_time;
    this->number_of_people = people;
    this->link = link;
}

Event::Event(const Event &e) {
    this->title = e.title;
    this->description = e.description;
    this->date_and_time = e.date_and_time;
    this->number_of_people = e.number_of_people;
    this->link = e.link;
}

string Event::getTitle() const {
    return this->title;
}

string Event::getDescription() const {
    return this->description;
}

string Event::getDateAndTime() const {
    return this->date_and_time;
}

int Event::getNumberOfPeople() const {
    return this->number_of_people;
}

string Event::getLink() const {
    return this->link;
}

string Event::getDay() const {
    return this->date_and_time.substr(0, 2);
}

string Event::getMonth() const {
    return this->date_and_time.substr(3, 2);
}

string Event::getYear() const {
    return this->date_and_time.substr(6, 4);
}

string Event::getTime() const {
    return this->date_and_time.substr(11, 5);
}

void Event::setTitle(const string &new_title) {
    this->title = new_title;
}

void Event::setDescription(const string &new_description) {
    this->description = new_description;
}

void Event::setDateAndTime(const string &new_date_and_time) {
    this->date_and_time = new_date_and_time;
}

void Event::setLink(const string &new_link) {
    this->link = new_link;
}

void Event::setNumberOfPeople(int new_people) {
    this->number_of_people = new_people;
}

void Event::increase() {
    this->number_of_people++;
}

void Event::decrease() {
    this->number_of_people--;
}
//
//void Event::print() {
//    std::cout << "Title: " << this->title << std::endl;
//    std::cout << "Description: " << this->description << std::endl;
//    std::cout << "Date: " << this->date_and_time << std::endl;
//    std::cout << "People: " << this->number_of_people << std::endl;
//    std::cout << "Link: " << this->link << std::endl;
//}

bool Event::operator==(const Event &other) {
    return this->title == other.getTitle();
}

bool Event::operator==(const std::string &other) {
    return this->title == other;
}


Event &Event::operator=(const Event &other) {
    this->title = other.getTitle();
    this->description = other.getDescription();
    this->date_and_time = other.getDateAndTime();
    this->number_of_people = other.getNumberOfPeople();
    this->link = other.getLink();

    return *this;
}

istream &operator>>(istream &is, Event &e) {
    string line;
    getline(is, line);

    vector<string> tokens = tokenize(line, ',');

    if (tokens.size() != 5) {
        return is;
    }

    e.title = tokens[0];
    e.description = tokens[1];
    e.date_and_time = tokens[2];
    e.number_of_people = stoi(tokens[3]);
    e.link = tokens[4];

    return is;
}

ostream &operator<<(ostream &os, Event &e) {
    os << e.getTitle() << "|" << e.getDescription() << "|" << e.getDateAndTime() << "|" <<e.getNumberOfPeople()<< "|"<< e.getLink() << endl;
    return os;
}

