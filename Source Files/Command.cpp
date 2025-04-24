#include "Command.h"

#include <utility>


void History::execute(std::unique_ptr<Command> command) {
    command->execute();
    commands.push_back(std::move(command));
    undoneCommands.clear();
}

void History::undo() {
    if (!commands.empty()) {
        commands.back()->unexecute();
        undoneCommands.push_back(std::move(commands.back()));
        commands.pop_back();
    }else{
        throw std::runtime_error("No more undos");

    }
}

void History::redo() {
    if (!undoneCommands.empty()) {
        undoneCommands.back()->execute();
        commands.push_back(std::move(undoneCommands.back()));
        undoneCommands.pop_back();
    } else{
        throw std::runtime_error("No more redos");
    }
}

void History::clear() {

    this->commands.clear();
    this->undoneCommands.clear();

}


UpdateDescriptionCommand::UpdateDescriptionCommand(Repository& repo, std::string title, std::string newDescription, std::string oldDescription) :
repo{repo}, title{std::move(title)}, newDescription{std::move(newDescription)}, oldDescription{std::move(oldDescription)} {
}
void UpdateDescriptionCommand::execute() {
    repo.updateEventDescription(title, newDescription);
}
void UpdateDescriptionCommand::unexecute() {
    repo.updateEventDescription(title, oldDescription);
}

UpdateDateCommand::UpdateDateCommand(Repository& repo, std::string title, std::string newDate, std::string oldDate):
        repo{repo}, title{std::move(title)}, newDate{std::move(newDate)}, oldDate{std::move(oldDate)} {
}
void UpdateDateCommand::execute() {
    repo.updateEventDate(title, newDate);
}
void UpdateDateCommand::unexecute() {
    repo.updateEventDate(title, oldDate);
}

UpdatePeopleCommand::UpdatePeopleCommand(Repository& repo, std::string title, int newPeople, int oldPeople):
        repo{repo}, title{std::move(title)}, newPeople{newPeople}, oldPeople{oldPeople} {
}
void UpdatePeopleCommand::execute() {
    repo.updateEventPeople(title, newPeople);
}
void UpdatePeopleCommand::unexecute() {
    repo.updateEventPeople(title, oldPeople);
}

UpdateTitleCommand::UpdateTitleCommand(Repository& repo, std::string title, std::string newTitle, std::string oldTitle):
        repo{repo}, title{std::move(title)}, newTitle{std::move(newTitle)}, oldTitle{std::move(oldTitle)} {
}
void UpdateTitleCommand::execute() {
    repo.updateEventTitle(title, newTitle);
}
void UpdateTitleCommand::unexecute() {
    repo.updateEventTitle(title, oldTitle);
}

UpdateLinkCommand::UpdateLinkCommand(Repository& repo, std::string title, std::string newLink, std::string oldLink):
        repo{repo}, title{std::move(title)}, newLink{std::move(newLink)}, oldLink{std::move(oldLink)} {
}
void UpdateLinkCommand::execute() {
    repo.updateEventLink(title, newLink);
}
void UpdateLinkCommand::unexecute() {
    repo.updateEventLink(title, oldLink);
}


AddCommand::AddCommand(Repository& repo, const Event& event): repo{repo}{
    title = event.getTitle();
    description = event.getDescription();
    date = event.getDateAndTime();
    people = event.getNumberOfPeople();
    link = event.getLink();
}
void AddCommand::execute() {
    Event event(title, description, date, people, link);
    repo.addEvent(event);
}
void AddCommand::unexecute() {
    repo.removeEvent(title);
}

RemoveCommand::RemoveCommand(Repository& repo, const Event& event): repo{repo} {
    title = event.getTitle();
    description = event.getDescription();
    date = event.getDateAndTime();
    people = event.getNumberOfPeople();
    link = event.getLink();
}
void RemoveCommand::execute() {
    repo.removeEvent(title);
}
void RemoveCommand::unexecute() {
    Event event(title, description, date, people, link);
    repo.addEvent(event);
}


UserAddCommand::UserAddCommand(Repository &repo, const Event &event):repo{repo}, event(event) {
}
void UserAddCommand::execute() {
    repo.addEventToUserList(event);
}
void UserAddCommand::unexecute() {
    repo.removeEventFromUserList(event.getTitle());
}

UserRemoveCommand::UserRemoveCommand(Repository &repo, const Event &event):repo{repo}, event(event) {
}
void UserRemoveCommand::execute() {
    repo.removeEventFromUserList(event.getTitle());
}
void UserRemoveCommand::unexecute() {
    repo.addEventToUserList(event);
}