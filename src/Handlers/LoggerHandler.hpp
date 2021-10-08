#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "../TaskPool/TaskPool.hpp"

class LoggerHandler{
private:
    std::ofstream _logfile;
public:
    LoggerHandler(const char*);
    LoggerHandler(std::string&);
    ~LoggerHandler();
    void handle(char*);
};