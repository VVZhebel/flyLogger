#pragma once

#include "Modules/RequestModule.hpp"

class Statistics{
private:
    IModule* _module;
    Statistics();
    ~Statistics();
    Statistics(const Statistics&)=delete;
    Statistics operator=(const Statistics&)=delete;
public:
    static Statistics& getStat();
    void process(const Task&);
    json data();
};