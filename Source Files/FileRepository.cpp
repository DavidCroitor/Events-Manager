#include "FileRepository.h"

#include <fstream>
#include <utility>
#include <algorithm>

FileRepository::FileRepository(std::string path, int type) : Repository(path) {
    if(type ==1){
        writer = new HTMLWriter("../userEvents.html", *this);
    }
    else if(type == 2){
        writer = new CSVWriter("../userEvents.csv", *this);
    }
    loadFromFile();
}

void FileRepository::addEvent(Event &e) {
    Repository::addEvent(e);
    this->writer->writeToFile();
}

void FileRepository::removeEvent(const std::string &title) {
    Repository::removeEvent(title);
    this->writer->writeToFile();
}



bool FileRepository::updateEventTitle(const std::string &title, const std::string &new_title) {
    if (Repository::updateEventTitle(title, new_title)) {
        this->writer->writeToFile();
        return true;
    }
    return false;
}

bool FileRepository::updateEventDescription(const std::string &title, const std::string &new_description) {
    if (Repository::updateEventDescription(title, new_description)) {
        this->writer->writeToFile();
        return true;
    }
    return false;
}

bool FileRepository::updateEventDate(const std::string &title, const std::string &new_date) {
    if (Repository::updateEventDate(title, new_date)) {
        this->writer->writeToFile();
        return true;
    }
    return false;
}

bool FileRepository::updateEventPeople(const std::string &title, int new_number) {
    if (Repository::updateEventPeople(title, new_number)) {
        this->writer->writeToFile();
        return true;
    }
    return false;
}

bool FileRepository::updateEventLink(const std::string &title, const std::string &new_link) {
    if (Repository::updateEventLink(title, new_link)) {
        this->writer->writeToFile();
        return true;
    }
    return false;
}

void FileRepository::increase(const std::string &title) {
    Repository::increase(title);
    this->writer->writeToFile();
}

void FileRepository::decrease(const std::string &title) {
    Repository::decrease(title);
    this->writer->writeToFile();
}

FileRepository::~FileRepository() {
//    this->writer->writeToFile();
}

void FileRepository::addEventToUserList(Event &event) {
    Repository::addEventToUserList(event);
    this->writer->writeToFile();
}

void FileRepository::removeEventFromUserList(const string &title) {
    Repository::removeEventFromUserList(title);
    this->writer->writeToFile();
}
