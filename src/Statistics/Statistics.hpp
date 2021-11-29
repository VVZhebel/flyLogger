#pragma once

#include "Modules/RequestModule.hpp"
#include <unordered_map>

class Statistics{
private:
    std::unordered_map<std::string, IModule*> _modules;
    Statistics();
    ~Statistics();
    Statistics(const Statistics&)=delete;
    Statistics operator=(const Statistics&)=delete;
public:
    static Statistics& getStat();
    void process(const Task&);
    json data();
};