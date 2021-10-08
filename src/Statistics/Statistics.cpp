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
    _module->count(T);
}

json Statistics::data(){
    return _module->toJson();
}
