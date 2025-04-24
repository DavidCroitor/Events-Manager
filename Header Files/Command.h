#pragma once
#include "Repository.h"

#include <memory>
#include <vector>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class UpdateDescriptionCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string oldDescription;
    std::string newDescription;
public:
    UpdateDescriptionCommand(Repository& repo, std::string  title, std::string  newDescription, std::string  oldDescription);
    void execute() override;
    void unexecute() override;

};

class UpdateDateCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string oldDate;
    std::string newDate;
public:
    UpdateDateCommand(Repository& repo, std::string  title, std::string  newDate, std::string oldDate);
    void execute() override;
    void unexecute() override;
};

class UpdatePeopleCommand : public Command {
private:
    Repository& repo;
    std::string title;
    int oldPeople;
    int newPeople;
public:
    UpdatePeopleCommand(Repository& repo, std::string  title, int newPeople, int oldPeople);
    void execute() override;
    void unexecute() override;
};

class UpdateTitleCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string oldTitle;
    std::string newTitle;
public:
    UpdateTitleCommand(Repository& repo, std::string  title, std::string  newTitle, std::string  oldTitle);
    void execute() override;
    void unexecute() override;
};

class UpdateLinkCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string oldLink;
    std::string newLink;
public:
    UpdateLinkCommand(Repository& repo, std::string  title, std::string  newLink, std::string oldLink);
    void execute() override;
    void unexecute() override;
};

class AddCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string description;
    std::string date;
    int people;
    std::string link;
public:
    AddCommand(Repository& repo, const Event& event);
    void execute() override;
    void unexecute() override;
};

class RemoveCommand : public Command {
private:
    Repository& repo;
    std::string title;
    std::string description;
    std::string date;
    int people;
    std::string link;
public:
    RemoveCommand(Repository& repo, const Event& event);
    void execute() override;
    void unexecute() override;
};

class UserAddCommand : public Command {
private:
    Repository& repo;
    Event event;
public:
    UserAddCommand(Repository& repo, const Event& event);
    void execute() override;
    void unexecute() override;
};

class UserRemoveCommand : public Command {
private:
    Repository& repo;
    Event event;
public:
    UserRemoveCommand(Repository& repo, const Event& event);
    void execute() override;
    void unexecute() override;

};

class History {
    std::vector<std::unique_ptr<Command>> commands;
    std::vector<std::unique_ptr<Command>> undoneCommands;

public:
    void execute(std::unique_ptr<Command> command);
    void undo();
    void redo();

    void clear();
};
