#include "RepositoryException.h"

RepositoryException::RepositoryException() : std::exception(), message{""} {

}

RepositoryException::RepositoryException(const std::string &msg) : message{msg} {

}

const char *RepositoryException::what() {
    return this->message.c_str();
}

const char *DuplicateEventException::what() {
    return "Existing event with the same title!";
}

const char *InexistingEventException::what() {
    return "There is no such event!";
}
