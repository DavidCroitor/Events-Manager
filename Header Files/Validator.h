#pragma once
#include <string>
#include <exception>
#include "Event.h"

class ValidatorException: public std::exception{
private:
std::string message;
public:
    ValidatorException(std::string _message);
    const char *what() const noexcept override;
};

class Validator {
public:
    static void validate(const Event& e);
};

