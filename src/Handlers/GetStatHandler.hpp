#pragma once
#include "../TaskPool/SocketPool.hpp"

class GetStatHandler{
private:

public:
    GetStatHandler();
    ~GetStatHandler();
    void handle(int);
};