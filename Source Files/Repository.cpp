#include "../Header Files/Repository.h"
#include <algorithm>
#include "compareDates.h"
#include <fstream>
#include <utility>
#include "RepositoryException.h"

Repository::Repository() {
    this->events = std::vector<Event>();
    this->userList = std::vector<Event>();
}

Repository::Repository(std::string path):fileName(std::move(path)) {
    this->events = std::vector<Event>();
    this->userList = std::vector<Event>();
    loadFromFile();
}

void Repository::loadFromFile() {
    ifstream file(this->fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("File does not exist");

    }

    Event event;
    while (file >> event) {
        auto it = find(this->events.begin(), this->events.end(), event);
        if (it == this->events.end()) {
            this->events.push_back(event);
        }
    }

    file.close();
}

void Repository::writeToFile() {
    ofstream file(this->fileName);
    if (file.is_open()) {
        for (auto &event: this->events) {
            file << event.getTitle() << "," << event.getDescription() << "," << event.getDateAndTime() << ","
                 << event.getNumberOfPeople() << "," << event.getLink() << "\n";
        }
    }
    file.close();
}

int Repository::getPos(const std::string &title) {
    auto it = std::find(this->events.begin(), this->events.end(), title);
    if (it == this->events.end()) {
        return -1;
    } else {
        return int(it - this->events.begin());
    }
}

Event Repository::getEvent(const std::string &title) {
    int pos = getPos(title);
    if (pos == -1) {
        throw InexistingEventException();
    }
    return this->events.at(pos);
}

void Repository::addEvent(Event &event) {
    auto it = std::find(this->events.begin(), this->events.end(), event);
    if (it == this->events.end()) {
        this->events.push_back(event);
        this->writeToFile();
    }else{
        throw DuplicateEventException();
    }

}

void Repository::addEventToUserList(Event &event) {
    auto it = find(this->userList.begin(), this->userList.end(), event);
    if (it != this->userList.end()) {
        throw DuplicateEventException();
    }
    this->userList.push_back(event);
}

void Repository::removeEventFromUserList(const std::string &title) {
    auto it = std::find(this->userList.begin(), this->userList.end(), title);
    if(it == this->userList.end()){
        throw InexistingEventException();
    }
    if(it != this->userList.end()){
        this->userList.erase(it);
    }
}

void Repository::removeEvent(const string &title) {
    int pos = getPos(title);
    if( pos == -1){
        throw InexistingEventException();
    }
    this->events.erase(this->events.begin() + pos);
    this->writeToFile();
}

std::vector<Event> Repository::getAll() {
    std::vector<Event> result = this->events;
    sort(result.begin(), result.end(), &compareDates);
    return result;
}

std::vector<Event>Repository::getUserEvents() {
    return this->userList;
}

std::vector<Event> Repository::getEventsByMonth(const string &month) {
    std::vector<Event> result;
    std::copy_if(events.begin(), events.end(), std::back_inserter(result),
                 [&month](const Event &event) {
                     return event.getMonth() == month;
                 });
    sort(result.begin(), result.end(), &compareDates);
    return result;
}

bool Repository::updateEventTitle(const string &title, const string &new_title) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.setTitle(new_title);
            return true;
        }
    }
    return false;
}

bool Repository::updateEventDescription(const string &title, const string &new_description) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.setDescription(new_description);
            return true;
        }
    }
    return false;
}

bool Repository::updateEventDate(const string &title, const string &new_date) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.setDateAndTime(new_date);
            return true;
        }
    }
    return false;
}

bool Repository::updateEventLink(const string &title, const string &new_link) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.setLink(new_link);
            return true;
        }
    }
    return false;
}

bool Repository::updateEventPeople(const std::string &title, int new_number) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.setNumberOfPeople(new_number);
            return true;
        }
    }
    return false;
}

void Repository::increase(const std::string &title) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.increase();
            return;
        }
    }
}

void Repository::decrease(const std::string &title) {
    for (auto &event: this->events) {
        if (event.getTitle() == title) {
            event.decrease();
            return;
        }
    }
}

void Repository::generateEvents() {
    Event event1("Birthday Party", "Celebrating Alice's birthday", "10/04/2024 18:00", 20,
                 "https://example.com/birthday");
    Event event2("Conference", "Tech conference on AI", "15/05/2024 09:00", 100, "https://example.com/conference");
    Event event3("Wedding", "John and Emily's wedding ceremony", "20/07/2024 15:30", 150,
                 "https://example.com/wedding");
    Event event4("Meeting", "Project status update meeting", "25/04/2024 10:00", 10, "https://example.com/meeting");
    Event event5("Concert", "Rock band concert", "05/06/2024 20:00", 300, "https://example.com/concert");
    Event event6("Exhibition", "Art exhibition showcasing local artists", "12/08/2024 11:00", 50,
                 "https://example.com/exhibition");
    Event event7("Workshop", "Cooking workshop", "18/04/2024 14:00", 15, "https://example.com/workshop");
    Event event8("Seminar", "Educational seminar on finance", "30/05/2024 13:30", 80, "https://example.com/seminar");
    Event event9("Festival", "Cultural festival", "05/07/2024 12:00", 200, "https://example.com/festival");
    Event event10("Webinar", "Webinar on digital marketing", "08/09/2024 19:00", 50, "https://example.com/webinar");

    this->addEvent(event1);
    this->addEvent(event2);
    this->addEvent(event3);
    this->addEvent(event4);
    this->addEvent(event5);
    this->addEvent(event6);
    this->addEvent(event7);
    this->addEvent(event8);
    this->addEvent(event9);
    this->addEvent(event10);
}