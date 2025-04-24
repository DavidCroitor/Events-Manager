#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Event.h"
#include "Repository.h"

class Writer {
protected:
    std::string filename;
    Repository& repo;
public:
    Writer(std::string filename, Repository& repo);
    virtual void writeToFile() = 0;
    virtual ~Writer(){};
};

class HTMLWriter: public Writer{
public:
    HTMLWriter(std::string filename, Repository& repo);
    void writeToFile() override;
};

class CSVWriter: public Writer{
public:
    CSVWriter(std::string filename, Repository& repo);
    void writeToFile() override;
};