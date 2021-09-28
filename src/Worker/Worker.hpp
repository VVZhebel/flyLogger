#pragma once

#include <thread>

#include "../TaskPool/TaskPool.hpp"
#include "../Task/Task.hpp"
#include "../Statistics/Statistics.hpp"

class Worker{
private:
    std::thread T;
public:
    Worker();
    ~Worker();
};