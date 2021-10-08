#include "Servers/UDP_Server.hpp"
#include "Servers/TCP_Server.hpp"
#include "Handlers/LoggerHandler.hpp"
#include "Handlers/GetStatHandler.hpp"
#include "Worker/Worker.hpp"
#include "Storage/StatArray.hpp"
#include "TaskPool/SocketPool.hpp"
#include "Loader/Loader.hpp"
#include <iostream>
#include <signal.h>

#define TCP_WORKERS_COUNT 8
#define LOG_FILE_NAME "log_file_test.txt"


bool _Active;

void signal_callback(int signum)
{
    std::cout << "SIGINT recieved" << std::endl;
    _Active = false;
}

int main()
{
    Loader* L = new Loader(LOG_FILE_NAME);
    L->load();
    delete L;

    _Active = true;
    // Worker for task processing
    Worker W([]()
             {
                 std::string MSG;
                 while (true)
                 {
                     try
                     {
                         MSG = TaskPool::Pool().popTask();
                         std::cout << MSG << std::endl;
                     }
                     catch (...)
                     {
                         return;
                     }
                     Task T(MSG);
                     Statistics::getStat().process(T);
                 }
             });

    //TCP socket handling workers
    std::vector<Worker *> _tcp_workers;
    for (int i = 0; i < TCP_WORKERS_COUNT; ++i)
    {
        _tcp_workers.push_back(new Worker([]()
                                          {
                                              int socket;
                                              while (true)
                                              {
                                                  try
                                                  {
                                                      socket = SocketPool::Pool().popTask();
                                                  }
                                                  catch (...)
                                                  {
                                                      return;
                                                  }

                                                  json Response = Statistics::getStat().data();
                                                  std::string Response_str = Response.dump();
                                                  try{
                                                      send(socket, Response_str.c_str(), Response_str.length(), MSG_NOSIGNAL);
                                                      close(socket);
                                                  }
                                                  catch(...){
                                                      continue;
                                                  }
                                              }
                                          }));
    }


    //UDP server for logging
    LoggerHandler* LH = new LoggerHandler(LOG_FILE_NAME);
    UDP_Server<LoggerHandler> S(22222, LH);

    //TCP server for answer
    GetStatHandler* SH = new GetStatHandler();
    TCP_Server<GetStatHandler> TS(22223, 128, SH);
    signal(SIGINT, signal_callback);


    S.Start();
    TS.Start();

    while (_Active)
    {
        // Main loop
    }


    TaskPool::Pool().StopService();
    SocketPool::Pool().StopService();
    S.Stop();
    TS.Stop();

    delete LH;
    delete SH;
    for (auto &i : _tcp_workers)
        delete i;
}
