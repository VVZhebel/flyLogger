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

json RequestModule::toJson(){
    json R;
    R["common"] = _counter.toJson();
    json users = json::array();
    for (auto i=_users.begin(); i!=_users.end(); i++){
        json U = {};
        U["email"] = i->first;
        U["data"] = i->second.sum_last(WEEK_DAYS);
        users.push_back(U);
    }
    R["users"] = users;

    return R;
}