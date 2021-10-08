#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/un.h>
#include <thread>

#define BUF_SIZE 1024

template <class Handler>
class TCP_Server
{
private:
    int         _port;
    int         _limit;
    int         _listener;
    Handler*    _h;
    std::thread _thread;

public:
    bool isActive;
    TCP_Server(int port, int connection_limit, Handler *h) : _port(port), _limit(connection_limit), _listener(0), _h(h)
    {
        std::cout << "Creating server instance" << std::endl;
    }
    ~TCP_Server()
    {
        std::cout << "Destructing server instance" << std::endl;
        if (this->_listener > 0)
            this->Stop();
    }
    void Start()
    {
        _thread = std::thread([&]()
                              {
                                  std::cout << "Start tcp server" << std::endl;

                                  _listener = socket(AF_INET, SOCK_STREAM, 0);
                                  if (_listener < 0)
                                  {
                                      std::cerr << "Error while socket initialization" << std::endl;
                                      return;
                                  }
                                  std::cout << "Socket successfully initialized" << std::endl;

                                  struct sockaddr_in addr;
                                  std::memset(&addr, 0, sizeof(addr));
                                  addr.sin_family = AF_INET;
                                  addr.sin_addr.s_addr = INADDR_ANY;
                                  addr.sin_port = htons(this->_port);

                                  if (bind(_listener, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)))
                                  {
                                      std::cerr << "Error on binding stream socket" << std::endl;
                                      return;
                                  }

                                  std::cout << "Socket was successfully binded with port " << _port << std::endl;

                                  listen(_listener, _limit);
                                  isActive = true;

                                  for (;;)
                                  {
                                      int msgsock = accept(_listener, 0, 0);
                                      if (msgsock < 0)
                                      {
                                          std::cerr << "Error on accept" << std::endl;
                                          if (!isActive)
                                              break;
                                      }
                                      else
                                      {
                                          _h->handle(msgsock);
                                      }
                                  }
                                  std::cout << "Server thread was stopped" << std::endl;
                              });
    }
    void Stop()
    {
        isActive = false;
        std::cout << "Closing socket" << std::endl;
        shutdown(_listener, SHUT_RDWR);
        close(_listener);
        if (_thread.joinable())
            _thread.join();
    }
};