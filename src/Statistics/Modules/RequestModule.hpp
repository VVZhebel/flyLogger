#pragma once

#include "IModule.hpp"
#include "unordered_map"
#include <vector>

#define WEEK_DAYS 7
#define TOP_USERS_COUNT 5

class RequestModule: public IModule{
private:
    StatArray _counter;
    std::unordered_map<std::string, StatArray> _users;
public:
    RequestModule();
    ~RequestModule();
    void count(const Task&);
    json toJson();
};

bool comparePairsOfUsers(std::pair<std::string,int>&, std::pair<std::string,int>&);