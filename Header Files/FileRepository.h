#pragma once

#include "Repository.h"
#include "Writer.h"

class FileRepository : public Repository {
private:
    std::string fileName;
    Writer *writer;
public:
    FileRepository(string path, int type);

//    void writeToFile();

    void addEvent(Event &event) override;

    void addEventToUserList(Event &event) override;

    void removeEvent(const string &title) override;

    void removeEventFromUserList(const string &title) override;

    bool updateEventTitle(const string &title, const string &new_title) override;

    bool updateEventDescription(const string &title, const string &new_description) override;

    bool updateEventDate(const string &title, const string &new_date) override;

    bool updateEventLink(const string &title, const string &new_link) override;

    bool updateEventPeople(const string &title, int new_number) override;

    void increase(const string &title) override;

    void decrease(const string &title) override;

    ~FileRepository();
};
