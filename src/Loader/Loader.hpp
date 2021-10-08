#pragma once

#include <string>
#include <fstream>
#include "../TaskPool/TaskPool.hpp"

class Loader{
private:
    std::ifstream _file;
public:
    Loader(const char*);
    ~Loader();
    void load();
};