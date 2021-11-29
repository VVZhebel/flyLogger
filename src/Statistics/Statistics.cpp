#include "Statistics.hpp"

Statistics::Statistics(){
    _modules = {
        {"Common", new RequestModule()},
        {"Semantic", new RequestModule()},
        {"Document", new RequestModule()},
        {"Antiplag", new RequestModule()},
        {"Analytic", new RequestModule()},
        {"Scianalyze", new RequestModule()},
        {"Starsky", new RequestModule()}
    };

}

Statistics::~Statistics(){
    for (auto i=_modules.begin(); i!=_modules.end(); i++){
        delete i->second;
    }
}

Statistics& Statistics::getStat(){
    static Statistics S;
    return S;
}

void Statistics::process(const Task& T){
    _modules["Common"]->count(T);
    if (_modules.find(T.action) != _modules.end())
        _modules[T.action]->count(T);
}

json Statistics::data(){
    json R;
    for (auto i=_modules.begin(); i!=_modules.end(); i++)
        R[i->first] = i->second->toJson();
    return R;
}
