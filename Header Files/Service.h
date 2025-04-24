#pragma once
#include "Repository.h"
#include "FileRepository.h"
#include "Validator.h"
#include "Command.h"

class Service {
private:
    Repository& repository;
    History history;
    Validator validator;
public:
    Service(Repository& r);

    Event getEvent(const std::string& title);

    bool addEvent(const string &title, const string &description, const string &date, int people, const string &link);
    bool removeEvent(const string& title);
    void addUserEvent(Event &event);
    void removeUserEvent(const string &title);

    void updateEventTitle(const string& title, const string& new_title);
    void updateEventDescription(const string& title, const string& new_description);
    void updateEventDate(const string& title, const string& new_date);
    void updateEventLink(const string& title, const string& new_link);
    void updateEventPeople(const string& title, int new_number);
    void increase(const string& title);
    void decrease(const string& title);

    std::vector<Event> getAllEvents();
    std::vector<Event> getUserEvents();

    std::vector<Event> getEventsByMonth(const string& month);

    void undo();
    void redo();

    void clearHistory();
};
