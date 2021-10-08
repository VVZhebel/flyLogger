#include "SocketPool.hpp"

SocketPool::SocketPool():Active(true){

}
SocketPool::~SocketPool(){

}
SocketPool& SocketPool::Pool(){
    static SocketPool Pool;
    return Pool;
}

void SocketPool::pushTask(int socket){
    vectorLock.lock();
    Tasks.push(socket);
    semaphore.add();
    vectorLock.unlock();
}

int SocketPool::popTask(){
    semaphore.enter();
    if (!Active) throw -1;
    int result;
    vectorLock.lock();
    result=Tasks.front();
    Tasks.pop();
    vectorLock.unlock();
    return result;
}

void SocketPool::StopService(){
    std::cout<< "Stop socket pool" <<std::endl;
    Active = false; 
    semaphore.unleash();
}