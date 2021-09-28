#include "Statistics.hpp"

Statistics::Statistics(){
    _module = new RequestModule();
}

Statistics::~Statistics(){
    delete _module;
}

Statistics& Statistics::getStat(){
    static Statistics S;
    return S;
}

void Statistics::process(const Task& T){
    if (T.action == "PRINT")
        _module->print();
    else
        _module->count(T);
}
