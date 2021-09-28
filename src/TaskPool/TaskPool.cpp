#include "TaskPool.hpp"

TaskPool::TaskPool():Active(true){

}
TaskPool::~TaskPool(){

}
TaskPool& TaskPool::Pool(){
    static TaskPool Pool;
    return Pool;
}

void TaskPool::pushTask(std::string msg){
    vectorLock.lock();
    Tasks.push(msg);
    semaphore.add();
    vectorLock.unlock();
}

std::string TaskPool::popTask(){
    semaphore.enter();
    if (!Active) throw -1;
    std::string result;
    vectorLock.lock();
    result=Tasks.front();
    Tasks.pop();
    vectorLock.unlock();
    return result;
}

void TaskPool::StopService(){
    std::cout<< "Stop task pool" <<std::endl;
    Active = false; 
    semaphore.unleash();
}