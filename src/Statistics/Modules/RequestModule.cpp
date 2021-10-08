#include "RequestModule.hpp"

RequestModule::RequestModule(){

}
RequestModule::~RequestModule(){

}

void RequestModule::count(const Task& T){
    _counter[T.timestamp]++;
    if (_users.find(T.user) == _users.end())
        _users.insert({T.user, StatArray()});
    _users[T.user][T.timestamp]++;
}

void RequestModule::print(){
    std::cout << "COUNTER: " << std::endl;
    //_counter.print();
    std::cout << _counter.toJson().dump() << std::endl;
    std::cout << "USERS: " << std::endl;
    for (auto i=_users.begin(); i!=_users.end(); i++){
        std::cout << i->first << std::endl;
        //i->second.print();
        std::cout << i->second.toJson().dump() << std::endl;
    }
}

json RequestModule::toJson(){
    json R;
    R["common"] = _counter.toJson();
    json users = json::array();
    for (auto i=_users.begin(); i!=_users.end(); i++){
        json U = {};
        U["email"] = i->first;
        U["data"] = i->second.toJson();
        users.push_back(U);
    }
    R["users"] = users;

    return R;
}