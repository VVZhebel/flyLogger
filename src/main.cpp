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
#include <atomic>

#include "settings.hpp"


volatile bool _Active;

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
    UDP_Server<LoggerHandler> LS(UDP_PORT, LH);

    //TCP server for answer
    GetStatHandler* SH = new GetStatHandler();
    TCP_Server<GetStatHandler> TS(TCP_PORT, 128, SH);
    signal(SIGINT, signal_callback);


    LS.Start();
    TS.Start();

    while (_Active)
    {
        // Main loop
    }

    TaskPool::Pool().StopService();
    SocketPool::Pool().StopService();
    LS.Stop();
    TS.Stop();

    delete LH;
    delete SH;
    for (auto &i : _tcp_workers)
        delete i;
}
