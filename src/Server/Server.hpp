#pragma once
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

#include "../TaskPool/TaskPool.hpp"

#define MAX_BUF 1024

class Server{
    private:
        int           port;
        int           sock_fd;
        std::ofstream log;
        bool          _active;
    public:
        Server(int, const char*);
        Server(int,std::string&);
        ~Server();
        void Start();
        void Stop();
};