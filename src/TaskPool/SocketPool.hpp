#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include "Semaphore.hpp"
#include <iostream>

class SocketPool{
  private:
    SocketPool();
    ~SocketPool();
    SocketPool(SocketPool const &)=delete;
    SocketPool& operator= (SocketPool const &)=delete;

    std::queue<int>             Tasks;
    std::mutex                  vectorLock;
    std::condition_variable     queue_check;
    Semaphore                   semaphore;
  public:
    static SocketPool& Pool();
    void pushTask(int);
    int popTask();
    void StopService();
    bool Active;
};