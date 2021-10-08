#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <thread>

#define MAX_BUF 1024

template <class Handler>
class UDP_Server
{
private:
    int _port;
    int _sock_fd;
    bool _active;
    Handler *_h;
    std::thread _thread;

public:
    UDP_Server(int port, Handler *h) : _port(port), _h(h)
    {
    }
    ~UDP_Server()
    {
    }
    void Start()
    {
        _thread = std::thread([&]()
                              {
                                  struct sockaddr_in server;
                                  struct sockaddr_in client = {0};
                                  int msg_size;
                                  char BUF[MAX_BUF];

                                  _active = true;

                                  socklen_t client_len = sizeof(client);

                                  if ((_sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
                                  {
                                      std::cout << "socket creation failed" << std::endl;
                                      exit(EXIT_FAILURE);
                                  }

                                  server.sin_family = AF_INET;
                                  server.sin_addr.s_addr = INADDR_ANY;
                                  server.sin_port = htons(this->_port);

                                  if (bind(_sock_fd, (const struct sockaddr *)&server, sizeof(server)) < 0)
                                  {
                                      std::cout << "bind failed" << std::endl;
                                      std::cout << strerror(errno) << std::endl;
                                      exit(EXIT_FAILURE);
                                  }

                                  std::cout << "START udp server" << std::endl;

                                  while (_active)
                                  {
                                      memset(BUF, 0, MAX_BUF);
                                      msg_size = recvfrom(_sock_fd, (char *)BUF, MAX_BUF, 0, (struct sockaddr *)&client, &client_len);
                                      if (msg_size <= 0)
                                          continue;
                                      BUF[msg_size] = '\0';

                                      _h->handle(BUF);
                                  }

                                  std::cout << "STOP udp server" << std::endl;
                              });
    }
    void Stop()
    {
        _active = false;
        shutdown(_sock_fd, SHUT_RDWR);
        if (_thread.joinable())
            _thread.join();
    }
};