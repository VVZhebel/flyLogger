#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include "Semaphore.hpp"
#include <iostream>
#include <string>

class TaskPool{
  private:
    TaskPool();
    ~TaskPool();
    TaskPool(TaskPool const &)=delete;
    TaskPool& operator= (TaskPool const &)=delete;

    std::queue<std::string>     Tasks;
    std::mutex                  vectorLock;
    std::condition_variable     queue_check;
    Semaphore                   semaphore;
  public:
    static TaskPool& Pool();
    void pushTask(std::string);
    std::string popTask();
    void StopService();
    bool Active;
};