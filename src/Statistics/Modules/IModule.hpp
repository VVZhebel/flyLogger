#pragma once

#include <ctime>

#include "../../Task/Task.hpp"
#include "../../Storage/StatArray.hpp"

class IModule{
public:
    IModule(){

    }
    virtual ~IModule(){
        
    }
    virtual void count(const Task&)=0;
    virtual void print()=0;
};