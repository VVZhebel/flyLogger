#include "Server.hpp"


Server::Server(int port, const char* log_file_name){
    this->port = port;
    this->log.open(log_file_name, std::ios::out | std::ios::app);
}


Server::~Server(){
    this->log.flush();
    this->log.close();
}

void Server::Start(){
    struct sockaddr_in server;
    struct sockaddr_in client = {0};
    int msg_size;
    char BUF[MAX_BUF];

    _active = true;

    socklen_t client_len = sizeof(client);

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        std::cout << "socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(this->port);

    if (bind(sock_fd, (const struct sockaddr*)&server, sizeof(server)) < 0){
        std::cout << "bind failed" << std::endl;
        std::cout << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "START udp server" << std::endl;
    while (_active){
        memset(BUF, 0, MAX_BUF);
        msg_size = recvfrom(sock_fd, (char*)BUF, MAX_BUF, 0, (struct sockaddr *)&client, &client_len);
        if (msg_size <=0 )
            continue;
        BUF[msg_size] = '\0';
        std::stringstream MSG;

        MSG << std::time(0) << " " << BUF;

        TaskPool::Pool().pushTask(MSG.str());

        this->log << MSG.str() << std::endl;
    }
    std::cout << "STOP udp server" << std::endl;
}

void Server::Stop(){
    _active = false;
    close(sock_fd);
    TaskPool::Pool().StopService();
}