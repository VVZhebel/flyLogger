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
    std::vector<std::pair<std::string, int>> userstat={};
    json R;
    json users = json::array();
    R["common"] = _counter.toJson();

    for (auto i=_users.begin(); i!=_users.end(); i++){
        userstat.push_back(std::pair<std::string,int>({i->first, i->second.sum_last(WEEK_DAYS)}));
        std::push_heap(userstat.begin(), userstat.end(), comparePairsOfUsers);
    }

    std::sort_heap(userstat.begin(), userstat.end(), comparePairsOfUsers);

    if (userstat.size()>TOP_USERS_COUNT)
        userstat.resize(TOP_USERS_COUNT);

    for (auto &i:userstat){
        json user={
            {"user", i.first},
            {"count", i.second}
        };
        users.push_back(user);
    }

    R["users"] = users;

    return R;
}


bool comparePairsOfUsers(std::pair<std::string,int>& a, std::pair<std::string,int>& b){
    return a.second>b.second;
}