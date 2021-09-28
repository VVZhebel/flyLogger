#include "Task.hpp"

Task::Task(){
    timestamp = std::time(0);
    application = "";
    user = "";
    action = "";
}

Task::Task(std::string& input){
    std::stringstream I(input);
    I >> timestamp >> application >> action >> user;
}

Task::~Task(){

}

void Task::print(){
    std::cout << timestamp << " : " << application << " : " << action << " : " << user << std::endl;
}