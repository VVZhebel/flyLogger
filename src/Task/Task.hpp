#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>

class Task{
private:
public:
    Task();
    Task(std::string&);
    ~Task();

    std::time_t     timestamp;
    std::string     application;
    std::string     user;
    std::string     action;

    void print();
};