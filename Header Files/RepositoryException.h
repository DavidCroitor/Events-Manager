#pragma once
#include "Repository.h"
#include <string>
#include <exception>

class RepositoryException: public std::exception{
protected:
    std::string message;

public:

    RepositoryException();
    RepositoryException(const std::string& msg);
    virtual ~RepositoryException() {}
    virtual const char* what();
};


class DuplicateEventException: public RepositoryException
{
public:
    const char* what();
};

class InexistingEventException: public RepositoryException
{
public:
    const char* what();
};
