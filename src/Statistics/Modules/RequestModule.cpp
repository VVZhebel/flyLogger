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
    _counter.print();
    std::cout << "USERS: " << std::endl;
    for (auto i=_users.begin(); i!=_users.end(); i++){
        std::cout << i->first << std::endl;
        i->second.print();
    }
}