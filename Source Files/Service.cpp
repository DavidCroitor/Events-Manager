#include "../Header Files/Service.h"
#include <string>
#include <iostream>

using namespace std;

Service::Service(Repository &r):repository(r) {
}

bool Service::addEvent(const string& title, const string &description, const string &date, int people, const string &link) {

    if(this->repository.getPos(title)!=-1)
        throw ValidatorException("Event already exists!\n");

    Event event(title, description, date, people, link);
    Validator::validate(event);
    std::unique_ptr<Command> command = std::make_unique<AddCommand>(this->repository, event);
    this->history.execute(std::move(command));
    return true;
}

void Service::addUserEvent(Event &event) {
    std::unique_ptr<Command> command = std::make_unique<UserAddCommand>(this->repository, event);
    this->history.execute(std::move(command));
}

void Service::removeUserEvent(const std::string &title) {
    std::unique_ptr<Command> command = std::make_unique<UserRemoveCommand>(this->repository, this->repository.getEvent(title));
    this->history.execute(std::move(command));
}

bool Service::removeEvent(const string& title){
    std::unique_ptr<Command> command = std::make_unique<RemoveCommand>(this->repository, this->repository.getEvent(title));
    this->history.execute(std::move(command));
    return true;
}
Event Service::getEvent(const std::string &title) {
    return this->repository.getEvent(title);
}

void Service::updateEventTitle(const std::string &title, const std::string &new_title) {
    std::unique_ptr<Command> command = std::make_unique<UpdateTitleCommand>(this->repository, title, new_title, this->repository.getEvent(title).getTitle());
    this->history.execute(std::move(command));
}
void Service::updateEventDescription(const std::string &title, const std::string &new_description) {
    std::unique_ptr<Command> command = std::make_unique<UpdateDescriptionCommand>(this->repository, title, new_description, this->repository.getEvent(title).getDescription());
    this->history.execute(std::move(command));
}
void Service::updateEventDate(const std::string &title, const std::string &new_date) {
    std::unique_ptr<Command> command = std::make_unique<UpdateDateCommand>(this->repository, title, new_date, this->repository.getEvent(title).getDateAndTime());
    this->history.execute(std::move(command));
}
void Service::updateEventPeople(const std::string &title, int new_number) {
    std::unique_ptr<Command> command = std::make_unique<UpdatePeopleCommand>(this->repository, title, new_number, this->repository.getEvent(title).getNumberOfPeople());
    this->history.execute(std::move(command));
}
void Service::updateEventLink(const std::string &title, const std::string &new_link) {
    std::unique_ptr<Command> command = std::make_unique<UpdateLinkCommand>(this->repository, title, new_link, this->repository.getEvent(title).getLink());
    this->history.execute(std::move(command));
}
void Service::increase(const std::string &title) {
    this->repository.increase(title);
}
void Service::decrease(const std::string &title) {
    this->repository.decrease(title);
}

std::vector<Event> Service::getAllEvents(){
    return this->repository.getAll();
}
std::vector<Event> Service::getUserEvents() {
    return this->repository.getUserEvents();
}


std::vector<Event> Service::getEventsByMonth(const std::string &month){
    return this->repository.getEventsByMonth(month);
}

void Service::undo() {
    this->history.undo();
}

void Service::redo() {
    this->history.redo();
}

void Service::clearHistory() {
    this->history.clear();

}
