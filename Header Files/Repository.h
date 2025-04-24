#pragma once

#include <vector>
#include "Event.h"

#include <string>

class Repository {
friend class Writer;
protected:
    std::vector<Event> events;
    std::vector<Event> userList;
    std::string fileName;
public:

    Repository();
    Repository(std::string path);

    void loadFromFile();
    void writeToFile();

    virtual void addEvent(Event &event);
    virtual void removeEvent(const string &title);

    virtual void addEventToUserList(Event &event);
    virtual void removeEventFromUserList(const string &title);


    Event getEvent(const string &title);

    virtual bool updateEventTitle(const string &title, const string &new_title);

    virtual bool updateEventDescription(const string &title, const string &new_description);
    virtual bool updateEventDate(const string &title, const string &new_date);
    virtual bool updateEventLink(const string &title, const string &new_link);
    virtual bool updateEventPeople(const string &title, int new_number);
    virtual void increase(const string &title);
    virtual void decrease(const string &title);
    int getPos(const std::string &title);

    std::vector<Event> getAll();
    std::vector<Event> getUserEvents();

    std::vector<Event> getEventsByMonth(const string &month);


    //    DynamicVector<Event> events;



    void generateEvents();
};