#pragma once
#include <string>
#include <iostream>

using namespace std;

class Event{
private:
    string title;
    string description;
    string date_and_time;
    int number_of_people;
    string link;

public:
    Event();
    Event(const string& title, const string& description, const string& date_and_time, int people, const string& link);
    Event(const Event& other);

    string getTitle() const;
    string getDescription() const;
    string getDateAndTime() const;
    int getNumberOfPeople() const;
    string getLink() const;

    void increase();
    void decrease();

    void setTitle(const string& new_title);
    void setDescription(const string& new_description);
    void setDateAndTime(const string& new_date_and_time);
    void setNumberOfPeople(int new_people);
    void setLink(const string& new_link);

    bool operator==(const Event& other);
    bool operator==(const string& other);
    Event& operator=(const Event& other);

    string getYear() const;
    string getMonth() const;
    string getDay() const;
    string getTime() const;

//    void print();

    friend istream& operator>>(istream& ifs, Event& event);
    friend ostream& operator<<(ostream& ofs, Event& event);
};

